/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 17:55:37 by mcamila           #+#    #+#             */
/*   Updated: 2020/01/30 00:27:24 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_pt2	project_pt(t_pt3 pt3, double d)
{
	double xV;
	double yV;
	t_pt2 ptC;

	xV = ((pt3.x * d) / pt3.z);
	yV = ((pt3.y * d) / pt3.z);



	ptC.x = (xV * (WIDTH / 2) / 2) + WIDTH / 2;
	ptC.y = (yV * (HIEGHT/ 2) / 2 * (double)((double)WIDTH / (double)HIEGHT)) + HIEGHT / 2;
	return (ptC);
}

void	draw_triangle(t_inst_obj obj, t_tri tri, t_data *data, double d)
{
	t_pt3 p1;
	t_pt3 p2;
	t_pt3 p3;
	t_pt2 pt1;
	t_pt2 pt2;
	t_pt2 pt3;

	p1 = pt3_add(obj.ref_obj->pt[tri.pt[0]], obj.translate);
	p2 = pt3_add(obj.ref_obj->pt[tri.pt[1]], obj.translate);
	p3 = pt3_add(obj.ref_obj->pt[tri.pt[2]], obj.translate);

	pt1 = project_pt(p1, d);
	pt2 = project_pt(p2, d);
	pt3 = project_pt(p3, d);
//	draw_tri(pt1.x, pt1.y, 0.5f, pt2.x, pt2.y, 0, pt3.x, pt3.y, 1, data);
	draw_line(pt1.x, pt1.y, pt2.x, pt2.y, data, 0x00FFFFFF);
	draw_line(pt2.x, pt2.y, pt3.x, pt3.y, data, 0x00FFFFFF);
	draw_line(pt1.x, pt1.y, pt3.x, pt3.y, data, 0x00FFFFFF);

//	ft_putnbr(pt1.x);
//	ft_putstr(" ");
//	ft_putnbr(pt1.y);
//	ft_putstr("  ");
//	ft_putnbr(pt2.x);
//	ft_putstr(" ");
//	ft_putnbr(pt2.y);
//	ft_putstr("  ");
//	ft_putnbr(pt3.x);
//	ft_putstr(" ");
//	ft_putnbr(pt3.y);
//	ft_putstr("\n");
}

void	render_frame(t_inst_obj *objects, int  num_of_obj, t_data *data)
{
	int i;
	int j;

	i = 0;
	while (i < num_of_obj)
	{
		j = 0;
		while (j < objects[i].ref_obj->num_of_tris)
		{
			draw_triangle(objects[i], objects[i].ref_obj->tri[j], data, 1);
			j++;
		}
		i++;
	}
}