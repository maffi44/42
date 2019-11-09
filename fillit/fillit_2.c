/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjasper <bjasper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 17:29:19 by mcamila           #+#    #+#             */
/*   Updated: 2019/11/09 15:02:16 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int				ft_prepare_map(int len)
{
	int i;
	int j;
	int k;

	k = 0;
	i = 0;
	while (i < len)
	{
		j = 0;
		while (j < len)
		{
			map[i][j] = '.';
			j++;
		}
		map[i][j] = '\n';
		i++;
	}
	return (1);
}

int				ft_build_map(int tet, int row, int len)
{
	int i;

	i = 0;
	while (i < 4)
	{
//		printf("tet:%d row:%d, result:%d", tet, row, tets[tet].rows[row][i]);
		map[tets[tet].rows[row][i] / len][tets[tet].rows[row][i] % len] = 'A' + tet;
		i++;
	}
	return (1);
}

/*
 * i - index of current tetramino
 * j - index of column
 * imax - number of tatraminos
 * k - index of column elements
 * s - indexes of the next tetraminos
 */
void			ft_disable_rows(int j, int i, int imax)
{
	int k;
	int s;

	s = i;
	while (s < imax)
	{
//		printf("mask1.0: %lu\n",
		masks[i][s][0] = masks[i - 1][s][0];
//		printf("mask1.1: %lu\n",
		masks[i][s][1] = masks[i - 1][s][1];
		k = 0;
		while (k < cols[j][s].len)
		{
//			printf("cols elems value: %d, ", cols[j][s].elem[k]);
			masks[i][s][cols[j][s].elem[k] / 64] |= ((unsigned long)1 << (cols[j][s].elem[k] % 64));
			k++;
		}
		s++;
//		printf("mask2.0: %lu\n", masks[i][s][0]);
//		printf("mask2.1: %lu\n", masks[i][s][1]);
	}
//	printf("%lu %lu", masks[i][s][0], masks[i][s][0]);
}
/*
 * k - index of node
 */
void			ft_create_mask(int i, int j, int imax)
{
//	printf("create mask\n");
	int k;

	k = 0;
	while (k < 4)
	{
		ft_disable_rows(tets[i].rows[j][k], i + 1, imax);
		k++;
	}
}

int		ft_find_row()
{
	return (0);
}
/*
 * imax - number of tetrominos
 * i - index of current tetramino
 * j - index of a row (variants of tetromino's location) in current tetromino
 */
int		ft_Y(int imax, int i)
{
	short int	j;
	if (i == imax)
	{
//		printf("Fin!");
		return (ft_prepare_map(map_side));
	}
	j = 0;
	while (j < tets[i].length)
	{
		if (!((masks[i][i][j / 64] >> (j % 64)) & (unsigned long)1))
		{
//			printf("%d", i);
			ft_create_mask(i, j, imax);
			if (ft_Y(imax, i + 1))
				return (ft_build_map(i, j, map_side));
		}
		j++;
	}
	return (0);
}

void	ft_make_map(t_fill *figure, int imax, int length)
{
	int i;
	int j;
	int k;
	int m;
	int n;

	i = 0;
	while (i < imax)
	{
		n = 0;
		j = 0;
		while (j < length - (figure[i].y_len - 1))
		{
			k = 0;
			while (k < length - (figure[i].x_len - 1))
			{
				m = 0;
				while (m < 4)
				{
//					printf("tet:%d row:%d res:%d", i, n,
					tets[i].rows[n][m] =
							((k + (figure[i].sharp[m] % 10)) + (length * ((figure[i].sharp[m] / 10) + j)));
					cols[tets[i].rows[n][m]][i].elem[m] = n;
					cols[tets[i].rows[n][m]][i].len++;
					m++;
				}
				tets[i].length++;
				k++;
				n++;
			}
			j++;
		}
		i++;
	}
}

void	ft_draw_map()
{
	int i;
	int j;

	i = 0;
	while (i < map_side)
	{
		j = 0;
		while (j < map_side)
		{
			printf("%c", map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

void	ft_check_map(int imax)
{
	int i;
	int j;
	int k;

	i = 0;
	printf("rows:\n");
	while (i < imax)
	{
		printf("tetras %d:\n", i);
		j = 0;
		while (j < tets[i].length)
		{
			k = 0;
			while (k < 4)
			{
				printf("%d ",tets[i].rows[j][k]);
				k++;
			}
			j++;
			printf("\n");
		}
		i++;
		printf("\n");
	}
	printf("cols:\n");
	j = 0;
	while (j < map_side * map_side)
	{
		i = 0;
		printf("col %d:\n", j);
		while (i < imax) {
			k = 0;
			printf("tetra %d:\n", i);
			while (k < cols[j][i].len)
			{
				printf("%d ", cols[j][i].elem[k]);
				k++;
			}
			printf("\n");
			i++;
		}
		j++;
	}
}

void	ft_solve(int imax, int i, int side, t_fill *tetras)
{
	map_side = side;
	printf("side: %d\n", map_side);
	ft_make_map(tetras, imax, map_side);
	ft_check_map(imax);
	int j = 0;
	while (j < 26)
	{
		masks[0][j][0] = 0;
		masks[0][j][1] = 0;
		j++;
	}
//	ft_Y(imax, i);
	while (!(ft_Y(imax, i)))
		ft_make_map(tetras, imax, ++map_side);
	ft_draw_map();
}

















void ft_length(t_fill *a)
{
	int i;

	i = 0;
	a->x_len = a->sharp[i] % 10;
	a->y_len = a->sharp[i] / 10;
	++i;
	while (i < 4)
	{
		if (a->sharp[i] % 10 > a->x_len)
			a->x_len = a->sharp[i] % 10;
		if (a->sharp[i] / 10 > a->y_len)
			a->y_len = a->sharp[i] / 10;
		++i;
	}
	++a->x_len;
	++a->y_len;
}

void    ft_coordinates(int *a)
{
	int i;

	i = 0;
	while (i < 4)
	{
		a[i] = a[i] / 5 * 10 + a[i] % 5;
		++i;
	}
}

void    ft_upp(int *a)
{
	/*
	** Replace the tetramino to the upp and left position
	*/

	int i;

	while (a[0] % 5 != 0 && a[1] % 5 != 0 && a[2] % 5 != 0 && a[3] % 5 != 0)
	{
		i = 0;
		while (i < 4)
		{
			a[i] -= 1;
			++i;
		}
	}
	while (a[0] > 3 && a[1] > 3 && a[2] > 3 && a[3] > 3)
	{
		i = 0;
		while (i < 4)
		{
			a[i] -= 5;
			++i;
		}
	}
}

int is_figure_valid(char *buf, int i)
{
	/*
	** Check connections between sharps
	*/

	int connect;

	connect = 0;
	if (buf[i - 1] == '#')
		++connect;
	if (buf[i - 5] == '#')
		++connect;
	return (connect);
}

int validity(int fd, char *buf, t_fill *figure)
{
	/*
	** check validity of input tetrominos. If invalid - return 0.
	*/

	int ret;
	int i;
	int tetnum;
	int connect;

	tetnum = 0;
	while((ret = read(fd, buf, BUFF_SIZE))) //read one tetramino
	{
		connect = 0;
		i = 0;
		if (ret < 20 || (ret == 21 && buf[20] != '\n') || tetnum > 26)
			exit(0);
		ret = 0;
		while (i < 20)  //check validity of possible simbols in tetrominos
		{
			if (buf[i] == '.' && (i + 1) % 5 != 0)
				++i;
			else if (buf[i] == '\n' && (i + 1) % 5 == 0)
				++i;
			else if (buf[i++] == '#' && i % 5 != 0 && ret < 4)
			{
				figure[tetnum].sharp[ret] = i - 1; //memorize indexes of sharps
				connect = connect + is_figure_valid(buf, i - 1);
				++ret;
			}
			else
				return (0);
		}
		if (ret != 4 || (connect != 3 && connect != 4)) //check validity of sharp's numbers and tetramino figure
			exit(0);
		ft_upp(figure[tetnum].sharp);
		ft_coordinates(figure[tetnum].sharp);
		ft_length(&figure[tetnum]);
		++tetnum;
	}
	return (tetnum);
}

int		main(int argc, char **argv)
{
	int		fd;
	char	buf[BUFF_SIZE];
	t_fill	tetras[26];
	int n;
	int i;
	int j;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0 || argc != 2)
		exit(0);
	n = validity(fd, buf, tetras);
	int h = 0;
	while (h * h < n * 4)
		h++;
	ft_solve(n, 0, h, tetras);
	i = 0;
//	while (i < n)
//	{
//		printf("%d: x - %d y - %d\n", i, tetras[i].x_len, tetras[i].y_len);
//		j = 0;
//		while (j < 4)
//		{
//			printf("%d \n",tetras[i].sharp[j]);
//			j++;
//		}
//		ft_putchar('\n');
//		i++;
//	}
	return (0);
}