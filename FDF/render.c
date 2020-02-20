/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 17:55:37 by mcamila           #+#    #+#             */
/*   Updated: 2020/02/20 15:26:08 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

typedef struct		s_screen_tri
{
	t_pt2	pt1;
	t_pt2	pt2;
	t_pt2	pt3;
}					t_sc_tri;

typedef struct		s_space_tri
{
	char 	bool;
	t_vec3	vertex1;
	t_vec3	vertex2;
	t_vec3	vertex3;
	t_vec3	normal;
	t_vec3	light_vector1;
	t_vec3	light_vector2;
	t_vec3	light_vector3;
}					t_sp_tri;

t_sc_tri	make_screen_tri(t_sp_tri sp, t_data *data, t_inst_obj obj, t_tri tri);
t_vec3			seek_tri_center(t_vec3 vertex1, t_vec3 vertex2, t_vec3 vertex3);
t_sp_tri		make_tri_in_space(t_inst_obj obj, t_tri tri, float d);

inline t_vec3	seek_tri_center(t_vec3 vertex1, t_vec3 vertex2, t_vec3 vertex3)
{
	t_vec3 tri_center;

	tri_center.elem[0] = (vertex1.elem[0] + vertex2.elem[0] + vertex3.elem[0]) / 3;
	tri_center.elem[1] = (vertex1.elem[1] + vertex2.elem[1] + vertex3.elem[1]) / 3;
	tri_center.elem[2] = (vertex1.elem[2] + vertex2.elem[2] + vertex3.elem[2]) / 3;
	tri_center.elem[3] = (vertex1.elem[3] + vertex2.elem[3] + vertex3.elem[3]) / 3;
	return (tri_center);
}

inline t_sp_tri		make_tri_in_space(t_inst_obj obj, t_tri tri, float d)
{
	t_sp_tri tr;
	t_vec3	edge1;
	t_vec3	edge2;
	t_vec3	tri_center;


	tr.bool = 1;
	if (((tr.vertex1 = vec3_transform(
			obj.transform,
			obj.ref_obj->vertex[tri.pt[0]]))
				 .elem[2] / tr.vertex1.elem[3]) < d)
		return (tr);
	if (((tr.vertex2 = vec3_transform(
			obj.transform,
			obj.ref_obj->vertex[tri.pt[1]]))
				 .elem[2] / tr.vertex2.elem[3]) < d)
		return (tr);
	if (((tr.vertex3 = vec3_transform(
			obj.transform,
			obj.ref_obj->vertex[tri.pt[2]]))
				 .elem[2] / tr.vertex3.elem[3]) < d)
		return (tr);
	edge1 = vec_divide(tr.vertex1, tr.vertex2);
	edge2 = vec_divide(tr.vertex1, tr.vertex3);
	tri_center = seek_tri_center(tr.vertex1, tr.vertex2, tr.vertex3);
	tr.normal = vec_mult(edge1, edge2);
	if (vec_scalar_mult(tr.normal, tri_center) <= 0)
		return (tr);
	tr.bool = 0;
	return (tr);
}

inline t_sc_tri	make_screen_tri(t_sp_tri sp, t_data *data, t_inst_obj obj, t_tri tri)
{
	t_sc_tri sc;

	sp.normal = normalize_vec(sp.normal);
	sp.light_vector1 = vec_divide(data->dir_light, sp.vertex1);
	sp.light_vector1 = normalize_vec(sp.light_vector1);
	sp.light_vector2 = vec_divide(data->dir_light, sp.vertex2);
	sp.light_vector2 = normalize_vec(sp.light_vector2);
	sp.light_vector3 = vec_divide(data->dir_light, sp.vertex3);
	sp.light_vector3 = normalize_vec(sp.light_vector3);
	sc.pt1 = make_pt2_from_v3(sp.vertex1, data->d);
	sc.pt2 = make_pt2_from_v3(sp.vertex2, data->d);
	sc.pt3 = make_pt2_from_v3(sp.vertex3, data->d);
	sc.pt1.light = vec_scalar_mult(sp.normal, sp.light_vector1) * 0.95f;
	sc.pt2.light = vec_scalar_mult(sp.normal, sp.light_vector2) * 0.95f;
	sc.pt3.light = vec_scalar_mult(sp.normal, sp.light_vector3) * 0.95f;
	sc.pt1.color.ARGB = obj.ref_obj->vertex[tri.pt[0]].color;
	sc.pt2.color.ARGB = obj.ref_obj->vertex[tri.pt[1]].color;
	sc.pt3.color.ARGB = obj.ref_obj->vertex[tri.pt[2]].color;
	return (sc);
}

void	draw_triangle(t_inst_obj obj, t_tri tri, t_data *data, float d)
{
	t_sp_tri		space_tri;
	t_sc_tri	screen_tri;

	if ((space_tri = make_tri_in_space(obj, tri, d)).bool)
		return ;
	screen_tri = make_screen_tri(space_tri, data, obj, tri);
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
