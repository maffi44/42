/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 17:55:37 by mcamila           #+#    #+#             */
/*   Updated: 2020/01/24 21:08:23 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_pt2	canvas_pt(t_pt3 pt3, double d)
{
	int xV;
	int yV;
	t_pt2 ptC;

	xV = ((pt3.x * d) / pt3.z);
	yV = ((pt3.y * d) / pt3.z);

	ptC.x = xV * (WIDTH / 2) / (double)((double)WIDTH / (double)HIEGHT);
	ptC.y = yV * (HIEGHT/ 2) / (double)((double)HIEGHT / (double)WIDTH);
	return (ptC);
}

void	draw_triangle(t_3d_obj obj, t_tri tri, t_data *data, double d)
{
	t_pt2 pt1;
	t_pt2 pt2;
	t_pt2 pt3;

	pt1 = canvas_pt(obj.pt[tri.pt[0]], d);
	pt2 = canvas_pt(obj.pt[tri.pt[1]], d);
	pt3 = canvas_pt(obj.pt[tri.pt[2]], d);
	draw_line(pt1.x, pt1.y, pt2.x, pt2.y, data, 0x00FF0000);
	draw_line(pt2.x, pt2.y, pt3.x, pt3.y, data, 0x00FF0000);
	draw_line(pt1.x, pt1.y, pt3.x, pt3.y, data, 0x00FF0000);
}

void	render_frame(t_3d_obj *objects, int  num_of_obj, t_data *data)
{
	int i;
	int j;

	i = 0;
	while (i < num_of_obj)
	{
		j = 0;
		while (j < objects[i].num_of_tris)
		{
			draw_triangle(objects[i], objects[i].tri[j], data, 1.0f);
			j++;
		}
		i++;
	}
}