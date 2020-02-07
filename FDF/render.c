/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 17:55:37 by mcamila           #+#    #+#             */
/*   Updated: 2020/02/07 21:20:21 by mcamila          ###   ########.fr       */
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
	t_vec3 vertex1;
	t_vec3 vertex2;
	t_vec3 vertex3;
	t_vec3 normal;
	t_vec3 cam_vector;
	t_vec3 light_vector1;
	t_vec3 light_vector2;
	t_vec3 light_vector3;
	t_vec3 edge1;
	t_vec3 edge2;
	t_pt2 pt1;
	t_pt2 pt2;
	t_pt2 pt3;

	vertex1 = vec3_transform(
			obj.transform,
			obj.ref_obj->vertex[tri.pt[0]]
			);
	vertex2 = vec3_transform(
			obj.transform,
			obj.ref_obj->vertex[tri.pt[1]]
	);
	vertex3 = vec3_transform(
			obj.transform,
			obj.ref_obj->vertex[tri.pt[2]]
	);

	edge1 = vec_divide(vertex1, vertex2);
	edge2 = vec_divide(vertex1, vertex3);

	cam_vector.elem[0] = (vertex1.elem[0] + vertex2.elem[0] + vertex3.elem[0]) / 3;
	cam_vector.elem[1] = (vertex1.elem[1] + vertex2.elem[1] + vertex3.elem[1]) / 3;
	cam_vector.elem[2] = (vertex1.elem[2] + vertex2.elem[2] + vertex3.elem[2]) / 3;
	cam_vector.elem[3] = (vertex1.elem[3] + vertex2.elem[3] + vertex3.elem[3]) / 3;

	normal = vec_mult(edge1, edge2);
	if (vec_scalar_mult(normal, cam_vector) <= 0)
		return;

	pt1 = make_pt2_from_v3(vertex1);
	pt2 = make_pt2_from_v3(vertex2);
	pt3 = make_pt2_from_v3(vertex3);

	normal = normalize_vec(normal);
	light_vector1 = vec_divide(data->dir_light, vertex1);
	light_vector1 = normalize_vec(light_vector1);

	light_vector2 = vec_divide(data->dir_light, vertex2);
	light_vector2 = normalize_vec(light_vector2);

	light_vector3 = vec_divide(data->dir_light, vertex3);
	light_vector3 = normalize_vec(light_vector3);

	pt1.light = vec_scalar_mult(normal, light_vector1) * 0.95f;
	pt2.light = vec_scalar_mult(normal, light_vector2) * 0.95f;
	pt3.light = vec_scalar_mult(normal, light_vector3) * 0.95f;

	pt1.color.ARGB = obj.ref_obj->vertex[tri.pt[0]].color;
	pt2.color.ARGB = obj.ref_obj->vertex[tri.pt[1]].color;
	pt3.color.ARGB = obj.ref_obj->vertex[tri.pt[2]].color;

	draw_tri(pt1, pt2, pt3, data);
//	draw_line(pt1.x, pt1.y, pt2.x, pt2.y, data, 0x00FFFFFF);
//	draw_line(pt2.x, pt2.y, pt3.x, pt3.y, data, 0x00FFFFFF);
//	draw_line(pt1.x, pt1.y, pt3.x, pt3.y, data, 0x00FFFFFF);

//	ft_putnbr(tri.pt[0]);
//	ft_putstr("  ");
//	ft_putnbr(tri.pt[1]);
//	ft_putstr("  ");
//	ft_putnbr(tri.pt[02]);
//	ft_putstr("  ");
//	ft_putstr("\n");
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
	ft_bzero(data->zbuff, sizeof(float) * WIDTH * HIEGHT);
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
		color_loop(objects[i].ref_obj, 5);
		i++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
}