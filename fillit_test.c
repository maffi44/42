/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 17:29:19 by mcamila           #+#    #+#             */
/*   Updated: 2019/11/05 20:19:36 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct 	s_Tet
{
	short int	rows[121][4];
	short int	length;
}				t_Tet;

t_Tet			tets[26];
short int		cols[144][26][4];
unsigned char	masks[26][26][121];
/*
 * i - index of current tetramino
 * j - index of column
 * imax - number of tatraminos
 * k - index of column elements
 * s - indexes of the next tetraminos
 */
void			ft_disable_rows(int j, int i, int imax, unsigned char b)
{
	int k;
	int s;

	s = i;
	while (++s < imax)
	{
		k = 0;
		while (k < 4)
		{
			masks[i][s][cols[j][s][k]] = b;
			k++;
		}
	}
}
/*
 * k - index of node
 */
void			ft_create_mask(int i, int j, int imax, unsigned char b)
{
	int k;

	while (k < 4)
	{
		ft_disable_rows(tets[i].rows[j][k], i, imax, b);
		k++;
	}
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
		return (1);
	}
	j = 0;
	while (j < tets[i].length)
	{
		if (!(masks[i][i][j]))
		{
			ft_create_mask(i, j, imax, 1);
			if (ft_Y(im, i + 1))
				return (1);
			ft_create_mask(i, j, imax, 0);
		}
		j++;
	}
	return (0);
}

void	ft_solve(int imax, int i, int map_side)
{
	ft_make_map(map_side);
	while (!(ft_Y(imax, i)))
		ft_make_map(map_side + 1);
	ft_draw_map();
}