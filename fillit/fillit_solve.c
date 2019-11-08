/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 17:29:19 by mcamila           #+#    #+#             */
/*   Updated: 2019/11/08 18:48:57 by mcamila          ###   ########.fr       */
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
		masks[i][s][0] = masks[i - 1][s][0];
		masks[i][s][1] = masks[i - 1][s][1];
		k = 0;
		while (k < cols[j][s].len)
		{
			masks[i][s][cols[j][s].elem[k] / 64] |= (unsigned long)1 << (cols[j][s].elem[k] % 64);
			k++;
		}
		s++;
	}
}
/*
 * k - index of node
 */
void			ft_create_mask(int i, int j, int imax)
{
	int k;

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
		return (ft_prepare_map(map_side));
	j = 0;
	while (j < tets[i].length)
	{
		if (!((masks[i][i][j / 64] >> (j % 64)) & (unsigned long)1))
		{
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
					tets[i].rows[n][m] =
							((k + figure[i].sharp[m] % 10) + (length * ((figure[i].sharp[m] / 10) + k)));
					cols[tets[i].rows[n][m]][i].elem[m] = n;
					cols[tets[i].rows[n][m]][i].len++;
					n++;
					m++;
				}
				k++;
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
			write(1, &map[i][j], 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
}

void	ft_solve(int imax, int i, int side, t_fill *tetras)
{
	printf("solve");
	map_side = side;
	ft_make_map(tetras, imax, map_side);
	printf("make_map");
	while (!(ft_Y(imax, i)))
		ft_make_map(tetras, imax, map_side + 1);
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
	printf("1");
	int		fd;
	char	buf[BUFF_SIZE];
	t_fill	tetras[26];
	int n;
	int i;
	int j;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0 || argc != 2)
		exit(0);
	printf("1");
	n = validity(fd, buf, tetras);
	int h = 0;
	while (h * h < n * 4)
		h++;
	printf("1");
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



