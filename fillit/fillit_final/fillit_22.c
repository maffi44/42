/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit_22.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjasper <bjasper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 17:29:19 by mcamila           #+#    #+#             */
/*   Updated: 2019/11/11 22:05:13 by bjasper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static int				ft_prepare_map(t_main *main)
{
	int i;
	int j;
	int k;

	k = 0;
	i = 0;
	while (i < main->map_side)
	{
		j = 0;
		while (j < main->map_side)
		{
			main->map[i][j] = '.';
			j++;
		}
		main->map[i][j] = '\n';
		i++;
	}
	return (1);
}

static int				ft_build_map(int tet, int row, t_main *main)
{
	int i;

	i = 0;
	while (i < 4)
	{
		main->map[main->tets[tet].rows[row][i] / main->map_side]
		[main->tets[tet].rows[row][i] % main->map_side] = 'A' + tet;
		i++;
	}
	return (1);
}

/*
** i - index of current tetramino
** j - index of column
** imax - number of tatraminos
** k - index of column elements
** s - indexes of the next tetraminos
*/

static void				ft_disable_rows(int col_n, int i, t_main *main)
{
	int k;
	int s;

	s = i;
	while (s < main->imax)
	{
		k = 0;
		while (k < main->cols[col_n][s].len)
		{
			main->masks[i][s][main->cols[col_n][s].elem[k] / 64] |= ((unsigned
			long)1 << (main->cols[col_n][s].elem[k] % 64));
			k++;
		}
		s++;
	}
}

/*
** k - index of node
*/

static void				ft_create_mask(int i, int j, t_main *main)
{
	int k;

	k = i;
	while (k < main->imax)
	{
		main->masks[i + 1][k][0] = main->masks[i][k][0];
		main->masks[i + 1][k][1] = main->masks[i][k][1];
		k++;
	}
	k = 0;
	while (k < 4)
	{
		ft_disable_rows(main->tets[i].rows[j][k], i + 1, main);
		k++;
	}
}

/*
** imax - number of tetrominos
** i - index of current tetramino
** j - index of a row (variants of tetromino's location) in current tetromino
*/

int						ft_y(t_main *main, int i)
{
	short int	j;

	if (i == main->imax)
	{
		return (ft_prepare_map(main));
	}
	j = 0;
	while (j < main->tets[i].length)
	{
		if (!((main->masks[i][i][j / 64] >> (j % 64)) & (unsigned long)1))
		{
			ft_create_mask(i, j, main);
			if (ft_y(main, i + 1))
				return (ft_build_map(i, j, main));
		}
		j++;
	}
	return (0);
}
