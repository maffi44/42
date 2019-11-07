/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 17:29:19 by mcamila           #+#    #+#             */
/*   Updated: 2019/11/07 20:29:06 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct 	s_Tet
{
	int			rows[121][4];
	int			length;
}				t_Tet;

t_Tet			tets[26];
int				cols[144][26][4];
unsigned long	masks[26][26][2];
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
		while (k < 4)
		{
			masks[i][s][cols[j][s][k] / 64] |= (unsigned long)1 << (cols[j][s][k] % 64);
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
		return (1);
	j = 0;
	while (j < tets[i].length)
	{
		if (!((masks[i][i][j / 64] >> (j % 64)) & (unsigned long)1))
		{
			ft_create_mask(i, j, imax);
			if (ft_Y(imax, i + 1))
				return (1);
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

typedef struct	s_fill
{
	int			x_len;
	int			y_len;
	int			tetr[4];
}            	t_fill;

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
							((k + figure[i].tetr[m] % 10) + (length * ((figure[i].tetr[m] / 10) + k)));
					cols[tets[i].rows[n][m]][i][m] = n;
					n++;
					m++;
				}
				figure[i].tetr[0];
			}
		}
		i++;
	}
}