/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_triangles.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 05:14:02 by mcamila           #+#    #+#             */
/*   Updated: 2020/02/22 05:16:41 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	make_tri_1(t_tri *tri, int i, int j, int x)
{
	tri->pt[0] = (j * x) + i + 1;
	tri->pt[1] = (j * x) + i;
	tri->pt[2] = ((j + 1) * x) + i;
}

void	make_tri_2(t_tri *tri, int i, int j, int x)
{
	tri->pt[0] = ((j + 1) * x) + i + 1;
	tri->pt[1] = (j * x) + i + 1;
	tri->pt[2] = ((j + 1) * x) + i;
}

void	make_tri_3(t_tri *tri, int i, int j, int x)
{
	tri->pt[0] = (j * x) + i + 1;
	tri->pt[1] = (j * x) + i;
	tri->pt[2] = ((j + 1) * x) + i + 1;
}

void	make_tri_4(t_tri *tri, int i, int j, int x)
{
	tri->pt[0] = ((j + 1) * x) + i + 1;
	tri->pt[1] = (j * x) + i;
	tri->pt[2] = ((j + 1) * x) + i;
}

void	make_tris(t_ref_obj *obj, t_maps *maps, int x, int y)
{
	int i;
	int j;
	int k;

	k = 0;
	j = -1;
	while (++j < y - 1)
	{
		i = -1;
		while (++i < x - 1)
		{
			if (abs(maps->map[j][i] - maps->map[j + 1][i + 1])
				>= abs(maps->map[j + 1][i] - maps->map[j][i + 1]))
			{
				make_tri_1(&(obj->tri[k]), i, j, x);
				make_tri_2(&(obj->tri[k + 1]), i, j, x);
			}
			else
			{
				make_tri_3(&(obj->tri[k]), i, j, x);
				make_tri_4(&(obj->tri[k + 1]), i, j, x);
			}
			k += 2;
		}
	}
}
