/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 17:55:37 by mcamila           #+#    #+#             */
/*   Updated: 2020/01/30 14:51:57 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
/*
t_pt2	project_pt(t_vec3 pt3, double d)
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
*/
void	draw_triangle(t_inst_obj obj, t_tri tri, t_data *data, double d)
{
	t_vec3 p1;
	t_vec3 p2;
	t_vec3 p3;
	t_pt2 pt1;
	t_pt2 pt2;
	t_pt2 pt3;

	p1 = vec3_transform(
			obj.transform,
			obj.ref_obj->vertex[tri.pt[0]]
			);
	p2 = vec3_transform(
			obj.transform,
			obj.ref_obj->vertex[tri.pt[1]]
	);
	p3 = vec3_transform(
			obj.transform,
			obj.ref_obj->vertex[tri.pt[2]]
	);

	pt1 = make_pt2_from_v3(p1);
	pt2 = make_pt2_from_v3(p2);
	pt3 = make_pt2_from_v3(p3);
	draw_tri(pt1, pt2, pt3, 0.5f, 0, 1, data);
//	draw_line(pt1.x, pt1.y, pt2.x, pt2.y, data, 0x00FFFFFF);
//	draw_line(pt2.x, pt2.y, pt3.x, pt3.y, data, 0x00FFFFFF);
//	draw_line(pt1.x, pt1.y, pt3.x, pt3.y, data, 0x00FFFFFF);

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

//	mlx_destroy_image(data->mlx_ptr, data->img_ptr);
//	data->img_ptr = mlx_new_image(data->mlx_ptr, WIDTH, HIEGHT);
//	data->img_data = mlx_get_data_addr(data->img_ptr,
//									   &(data->bpp),
//									   &(data->img_line),
//									   &(data->endian));
	ft_bzero(data->img_data, WIDTH * HIEGHT * 4);
	bzero(data->zbuff, sizeof(double) * WIDTH * HIEGHT);
//	data->camera.transform = matrix_mult(data->camera.rotation, data->camera.translation);
	i = 0;
	while (i < num_of_obj)
	{
		objects[i].transform = make_transform_matrix(data->camera, objects[i]);
		j = 0;
		while (j < objects[i].ref_obj->num_of_tris)
		{
			draw_triangle(objects[i], objects[i].ref_obj->tri[j], data, 1);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
}