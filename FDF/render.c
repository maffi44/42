/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 17:55:37 by mcamila           #+#    #+#             */
/*   Updated: 2020/02/24 19:28:54 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

inline t_vec3	seek_tri_center(t_vec3 vertex1, t_vec3 vertex2, t_vec3 vertex3)
{
	t_vec3 tri_center;

	tri_center.elem[0] = (vertex1.elem[0]
			+ vertex2.elem[0] + vertex3.elem[0]) / 3;
	tri_center.elem[1] = (vertex1.elem[1]
			+ vertex2.elem[1] + vertex3.elem[1]) / 3;
	tri_center.elem[2] = (vertex1.elem[2]
			+ vertex2.elem[2] + vertex3.elem[2]) / 3;
	tri_center.elem[3] = (vertex1.elem[3]
			+ vertex2.elem[3] + vertex3.elem[3]) / 3;
	return (tri_center);
}

inline t_sp_tri	make_tri_in_space(t_inst_obj obj, t_tri tri, float d)
{
	t_sp_tri	tr;
	t_vec3		tri_center;

	tr.bool = 1;
	if ((((tr.vertex1 = vec3_transform(
			obj.transform,
			obj.ref_obj->vertex[tri.pt[0]]))
			.elem[2] / tr.vertex1.elem[3]) < d) ||
			(((tr.vertex2 = vec3_transform(
					obj.transform,
					obj.ref_obj->vertex[tri.pt[1]]))
					.elem[2] / tr.vertex2.elem[3]) < d) ||
					(((tr.vertex3 = vec3_transform(
							obj.transform,
							obj.ref_obj->vertex[tri.pt[2]]))
							.elem[2] / tr.vertex3.elem[3]) < d))
		return (tr);
	tr.edge1 = vec_divide(tr.vertex1, tr.vertex2);
	tr.edge2 = vec_divide(tr.vertex1, tr.vertex3);
	tr.normal = vec_mult(tr.edge1, tr.edge2);
	tri_center = seek_tri_center(tr.vertex1, tr.vertex2, tr.vertex3);
	if (vec_scalar_mult(tr.normal, tri_center) <= 0)
		return (tr);
	tr.bool = 0;
	return (tr);
}

inline t_sc_tri	mk_sc_tri(t_sp_tri sp, t_data *data, t_inst_obj obj, t_tri tri)
{
	t_sc_tri sc;

	sp.light_vector1 = vec_divide(data->dir_light, sp.vertex1);
	sp.light_vector1 = normalize_vec(sp.light_vector1);
	sp.light_vector2 = vec_divide(data->dir_light, sp.vertex2);
	sp.light_vector2 = normalize_vec(sp.light_vector2);
	sp.light_vector3 = vec_divide(data->dir_light, sp.vertex3);
	sp.light_vector3 = normalize_vec(sp.light_vector3);
	sp.normal = normalize_vec(sp.normal);
	sc.pt1 = make_pt2_from_v3(sp.vertex1, data->d);
	sc.pt2 = make_pt2_from_v3(sp.vertex2, data->d);
	sc.pt3 = make_pt2_from_v3(sp.vertex3, data->d);
	sc.pt1.light = vec_scalar_mult(sp.normal, sp.light_vector1) * 0.95f;
	sc.pt2.light = vec_scalar_mult(sp.normal, sp.light_vector2) * 0.95f;
	sc.pt3.light = vec_scalar_mult(sp.normal, sp.light_vector3) * 0.95f;
	sc.pt1.c.argb = obj.ref_obj->vertex[tri.pt[0]].color;
	sc.pt2.c.argb = obj.ref_obj->vertex[tri.pt[1]].color;
	sc.pt3.c.argb = obj.ref_obj->vertex[tri.pt[2]].color;
	return (sc);
}

void			draw_triangle(t_inst_obj obj, t_tri tri, t_data *data)
{
	t_sp_tri	space_tri;
	t_sc_tri	screen_tri;

	if ((space_tri = make_tri_in_space(obj, tri, data->d)).bool)
		return ;
	screen_tri = mk_sc_tri(space_tri, data, obj, tri);
	draw_tri(screen_tri.pt1, screen_tri.pt2, screen_tri.pt3, data);
}

void			render_frame(t_inst_obj *objects, int num_of_obj, t_data *data)
{
	int i;
	int j;

	ft_bzero(data->img_data, WIDTH * HIEGHT * 4);
	ft_bzero(data->zbuff, sizeof(float) * WIDTH * HIEGHT);
	i = 0;
	while (i < num_of_obj)
	{
		objects[i].transform = make_transform_matrix(objects[i]);
		j = -1;
		while (++j < objects[i].ref_obj->num_of_tris)
			draw_triangle(objects[i],
					objects[i].ref_obj->tri[j], data);
		if (data->q_bool)
			color_loop(objects[i].ref_obj, 4);
		i++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
}
