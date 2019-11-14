/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjasper <bjasper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 17:29:19 by mcamila           #+#    #+#             */
/*   Updated: 2019/11/12 14:13:09 by bjasper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static void	ft_make_rows(t_fill *figure, t_main *main, int i, int j)
{
	int n;
	int k;
	int m;

	n = 0;
	while (++j < main->map_side - (figure[i].y_len - 1))
	{
		k = -1;
		while (++k < main->map_side - (figure[i].x_len - 1))
		{
			m = -1;
			while (++m < 4)
			{
				main->tets[i].rows[n][m] = ((k + (figure[i].sharp[m] % 10))
				+ (main->map_side * ((figure[i].sharp[m] / 10) + j)));
				main->cols[main->tets[i].rows[n][m]][i]
				.elem[main->cols[main->tets[i].rows[n][m]][i].len] = n;
				main->cols[main->tets[i].rows[n][m]][i].len++;
			}
			main->tets[i].length++;
			n++;
		}
	}
}

static void	ft_make_map(t_fill *figure, t_main *main)
{
	int i;
	int j;

	i = -1;
	while (++i < 144)
	{
		j = -1;
		while (++j < 26)
			main->cols[i][j].len = 0;
	}
	i = -1;
	while (++i < main->imax)
	{
		main->tets[i].length = 0;
		j = -1;
		ft_make_rows(figure, main, i, j);
	}
}

static void	ft_draw_map(t_main *main)
{
	int i;
	int j;

	i = 0;
	while (i < main->map_side)
	{
		j = 0;
		while (j < main->map_side)
		{
			write(1, &(main->map[i][j]), 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
}

static void	ft_solve(int imax, int side, t_fill *tetras)
{
	t_main main;

	main.imax = imax;
	main.map_side = side;
	ft_make_map(tetras, &main);
	while (!(ft_y(&main, 0)))
	{
		main.map_side++;
		ft_make_map(tetras, &main);
	}
	ft_draw_map(&main);
}

int			main(int argc, char **argv)
{
	int		fd;
	char	buf[BUFF_SIZE];
	t_fill	tetras[26];
	int		i;
	int		j;

	fd = open(argv[1], O_RDONLY);
	if (argc != 2)
	{
		write(1, "fillit source_file\n", 19);
		exit(0);
	}
	if (fd < 0 || (i = ft_validity(fd, buf, tetras)) == 0)
	{
		write(1, "error\n", 6);
		exit(0);
	}
	j = 0;
	while (j * j < i * 4)
		j++;
	ft_solve(i, j, tetras);
}
