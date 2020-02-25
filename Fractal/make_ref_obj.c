/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_ref_obj.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 05:16:59 by mcamila           #+#    #+#             */
/*   Updated: 2020/02/24 19:27:52 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void		make_vertexes(t_ref_obj *obj, t_maps *maps, int x, int y)
{
	t_color		col;
	int			i;
	int			j;
	int			k;

	k = 0;
	col.argb = 0;
	j = -1;
	while (++j < y)
	{
		i = -1;
		while (++i < x)
		{
			col.colors[0] = maps->map[j][i] * 4;
			col.colors[1] = maps->map[j][i] * 1;
			col.colors[2] = maps->map[j][i] * 13;
			obj->vertex[k] = make_vertex((float)(i - x / 2),
					((float)maps->map[j][i]) / 5, (float)(j - y / 2), col.argb);
			k++;
		}
	}
}

t_ref_obj	make_ref_obj_from_map(int x, int y, t_data *data, t_maps *maps)
{
	t_ref_obj	obj;

	obj.num_of_pts = x * y;
	obj.num_of_tris = (x - 1) * (y - 1) * 2;
	obj.vertex = (t_vec3*)pmalloc(data, maps, sizeof(t_vec3) * obj.num_of_pts);
	obj.tri = (t_tri*)pmalloc(data, maps, sizeof(t_tri) * obj.num_of_tris);
	make_vertexes(&obj, maps, x, y);
	make_tris(&obj, maps, x, y);
	del_maps(maps);
	return (obj);
}
