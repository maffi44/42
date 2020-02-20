/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 17:55:37 by mcamila           #+#    #+#             */
/*   Updated: 2020/02/20 11:40:16 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

typedef struct		s_screen_tri
{
	t_pt2	pt1;
	t_pt2	pt2;
	t_pt2	pt3;
}					t_screen_tri;

typedef struct		s_space_tri
{
	t_vec3	vertex1;
	t_vec3	vertex2;
	t_vec3	vertex3;
	t_vec3	normal;
	t_vec3	light_vector1;
	t_vec3	light_vector2;
	t_vec3	light_vector3;
}					t_space_tri;

t_vec3	seek_tri_center(t_vec3 vertex1, t_vec3 vertex2, t_vec3 vertex3)
{
	t_vec3 tri_center;

	tri_center.elem[0] = (vertex1.elem[0] + vertex2.elem[0] + vertex3.elem[0]) / 3;
	tri_center.elem[1] = (vertex1.elem[1] + vertex2.elem[1] + vertex3.elem[1]) / 3;
	tri_center.elem[2] = (vertex1.elem[2] + vertex2.elem[2] + vertex3.elem[2]) / 3;
	tri_center.elem[3] = (vertex1.elem[3] + vertex2.elem[3] + vertex3.elem[3]) / 3;
	return (tri_center);
}

t_space_tri		*make_tri_in_space(t_space_tri *tr, t_inst_obj obj, t_tri tri, float d)
{
	t_vec3	edge1;
	t_vec3	edge2;
	t_vec3	tri_center;

	if (((tr->vertex1 = vec3_transform(
			obj.transform,
			obj.ref_obj->vertex[tri.pt[0]]))
				 .elem[2] / tr->vertex1.elem[3]) < d)
		return (NULL);
	if (((tr->vertex2 = vec3_transform(
			obj.transform,
			obj.ref_obj->vertex[tri.pt[1]]))
				 .elem[2] / tr->vertex2.elem[3]) < d)
		return (NULL);
	if (((tr->vertex3 = vec3_transform(
			obj.transform,
			obj.ref_obj->vertex[tri.pt[2]]))
				 .elem[2] / tr->vertex3.elem[3]) < d)
		return (NULL);
	edge1 = vec_divide(tr->vertex1, tr->vertex2);
	edge2 = vec_divide(tr->vertex1, tr->vertex3);
	tri_center = seek_tri_center(tr->vertex1, tr->vertex2, tr->vertex3);
	tr->normal = vec_mult(edge1, edge2);
	if (vec_scalar_mult(tr->normal, tri_center) <= 0)
		return (NULL);
	return (tr);
}

t_screen_tri	make_screen_tri(t_space_tri sp, t_data *data, t_inst_obj obj, t_tri tri)
{
	t_screen_tri tr;

	tr.pt1 = make_pt2_from_v3(sp.vertex1, data->d);
	tr.pt2 = make_pt2_from_v3(sp.vertex2, data->d);
	tr.pt3 = make_pt2_from_v3(sp.vertex3, data->d);

	sp.normal = normalize_vec(sp.normal);
	sp.light_vector1 = vec_divide(data->dir_light, sp.vertex1);
	sp.light_vector1 = normalize_vec(sp.light_vector1);

	sp.light_vector2 = vec_divide(data->dir_light, sp.vertex2);
	sp.light_vector2 = normalize_vec(sp.light_vector2);

	sp.light_vector3 = vec_divide(data->dir_light, sp.vertex3);
	sp.light_vector3 = normalize_vec(sp.light_vector3);

	tr.pt1.light = vec_scalar_mult(sp.normal, sp.light_vector1) * 0.95f;
	tr.pt2.light = vec_scalar_mult(sp.normal, sp.light_vector2) * 0.95f;
	tr.pt3.light = vec_scalar_mult(sp.normal, sp.light_vector3) * 0.95f;

	tr.pt1.color.ARGB = obj.ref_obj->vertex[tri.pt[0]].color;
	tr.pt2.color.ARGB = obj.ref_obj->vertex[tri.pt[1]].color;
	tr.pt3.color.ARGB = obj.ref_obj->vertex[tri.pt[2]].color;
	return (tr);
}

void	draw_triangle(t_inst_obj obj, t_tri tri, t_data *data, float d)
{
	t_space_tri space_tri;
	t_screen_tri	screen_tri;
	t_vec3	vertex1;
	t_vec3	vertex2;
	t_vec3	vertex3;
	t_vec3	normal;
	t_vec3	tri_center;
	t_vec3	light_vector1;
	t_vec3	light_vector2;
	t_vec3	light_vector3;
	t_vec3	edge1;
	t_vec3	edge2;
	t_pt2	pt1;
	t_pt2	pt2;
	t_pt2	pt3;

	if (!(make_tri_in_space(&space_tri, obj, tri, d)))
		return ;
	screen_tri = make_screen_tri(space_tri, data, obj, tri);
//	if (((vertex1 = vec3_transform(
//			obj.transform,
//			obj.ref_obj->vertex[tri.pt[0]]))
//				 .elem[2] / vertex1.elem[3]) < d)
//		return ;
//	if (((vertex2 = vec3_transform(
//			obj.transform,
//			obj.ref_obj->vertex[tri.pt[1]]))
//				 .elem[2] / vertex2.elem[3]) < d)
//		return ;
//	if (((vertex3 = vec3_transform(
//			obj.transform,
//			obj.ref_obj->vertex[tri.pt[2]]))
//				 .elem[2] / vertex3.elem[3]) < d)
//		return ;
//	edge1 = vec_divide(vertex1, vertex2);
//	edge2 = vec_divide(vertex1, vertex3);
//	tri_center = seek_tri_center(vertex1, vertex2, vertex3);
//	normal = vec_mult(edge1, edge2);
//	if (vec_scalar_mult(normal, tri_center) <= 0)
//		return ;

//	pt1 = make_pt2_from_v3(vertex1, d);
//	pt2 = make_pt2_from_v3(vertex2, d);
//	pt3 = make_pt2_from_v3(vertex3, d);
//
//	normal = normalize_vec(normal);
//	light_vector1 = vec_divide(data->dir_light, vertex1);
//	light_vector1 = normalize_vec(light_vector1);
//
//	light_vector2 = vec_divide(data->dir_light, vertex2);
//	light_vector2 = normalize_vec(light_vector2);
//
//	light_vector3 = vec_divide(data->dir_light, vertex3);
//	light_vector3 = normalize_vec(light_vector3);
//
//	pt1.light = vec_scalar_mult(normal, light_vector1) * 0.95f;
//	pt2.light = vec_scalar_mult(normal, light_vector2) * 0.95f;
//	pt3.light = vec_scalar_mult(normal, light_vector3) * 0.95f;
//
//	pt1.color.ARGB = obj.ref_obj->vertex[tri.pt[0]].color;
//	pt2.color.ARGB = obj.ref_obj->vertex[tri.pt[1]].color;
//	pt3.color.ARGB = obj.ref_obj->vertex[tri.pt[2]].color;

	draw_tri(screen_tri.pt1, screen_tri.pt2, screen_tri.pt3, data);
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
			color_loop(objects[i].ref_obj, 4);
		i++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
}
