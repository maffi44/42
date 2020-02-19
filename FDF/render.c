/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 17:55:37 by mcamila           #+#    #+#             */
/*   Updated: 2020/02/19 21:41:32 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	draw_triangle(t_inst_obj obj, t_tri tri, t_data *data, float d)
{
	t_vec3	vertex1;
	t_vec3	vertex2;
	t_vec3	vertex3;
	t_vec3	normal;
	t_vec3	cam_vector;
	t_vec3	light_vector1;
	t_vec3	light_vector2;
	t_vec3	light_vector3;
	t_vec3	edge1;
	t_vec3	edge2;
	t_pt2	pt1;
	t_pt2	pt2;
	t_pt2	pt3;

	if (((vertex1 = vec3_transform(
			obj.transform,
			obj.ref_obj->vertex[tri.pt[0]]))
				 .elem[2] / vertex1.elem[3]) < d)
		return ;
	if (((vertex2 = vec3_transform(
			obj.transform,
			obj.ref_obj->vertex[tri.pt[1]]))
				 .elem[2] / vertex2.elem[3]) < d)
		return ;
	if (((vertex3 = vec3_transform(
			obj.transform,
			obj.ref_obj->vertex[tri.pt[2]]))
				 .elem[2] / vertex3.elem[3]) < d)
		return ;
	edge1 = vec_divide(vertex1, vertex2);
	edge2 = vec_divide(vertex1, vertex3);

	cam_vector.elem[0] = (vertex1.elem[0] + vertex2.elem[0] + vertex3.elem[0]) / 3;
	cam_vector.elem[1] = (vertex1.elem[1] + vertex2.elem[1] + vertex3.elem[1]) / 3;
	cam_vector.elem[2] = (vertex1.elem[2] + vertex2.elem[2] + vertex3.elem[2]) / 3;
	cam_vector.elem[3] = (vertex1.elem[3] + vertex2.elem[3] + vertex3.elem[3]) / 3;

	normal = vec_mult(edge1, edge2);
	if (vec_scalar_mult(normal, cam_vector) <= 0)
		return;

	pt1 = make_pt2_from_v3(vertex1, d);
	pt2 = make_pt2_from_v3(vertex2, d);
	pt3 = make_pt2_from_v3(vertex3, d);

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
}

void	render_frame(t_inst_obj *objects, int num_of_obj, t_data *data)
{
	int i;
	int j;

	ft_bzero(data->img_data, WIDTH * HIEGHT * 4);
	ft_bzero(data->zbuff, sizeof(float) * WIDTH * HIEGHT);
	i = 0;
	while (i < num_of_obj)
	{
		objects[i].transform = make_transform_matrix(data->camera, objects[i]);
		j = 0;
		while (j < objects[i].ref_obj->num_of_tris)
		{
			draw_triangle(objects[i],
						  objects[i].ref_obj->tri[j], data, data->d);
			j++;
		}
		if (data->Q_bool)
			color_loop(objects[i].ref_obj, 5);
		i++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
}
