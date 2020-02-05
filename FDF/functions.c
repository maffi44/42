/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 12:42:03 by mcamila           #+#    #+#             */
/*   Updated: 2020/02/05 20:41:04 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
/*
t_vec3	pt3_add(t_vec3 pt1, t_vec3 pt2)
{
	pt1.x += pt2.x;
	pt1.y += pt2.y;
	pt1.z += pt2.z;
	return (pt1);
}
*/

void		color_loop(t_ref_obj *obj)
{
	t_color c;
	int i;

	i = 0;
	while (i < obj->num_of_pts)
	{
		c.ARGB = obj->vertex[i].color;
		c.colors[0] += i + 1;
		c.colors[1] -= i + 1;
		c.colors[2] -= obj->num_of_pts - i;
//		c.colors[1] += 3;
//		c.colors[2] -= 2;
		obj->vertex[i].color = c.ARGB;
		c.ARGB = 0;
		i++;
	}
}

t_inst_obj	make_obj_inst(t_ref_obj *ref)
{
	t_inst_obj	new_inst;

	new_inst.ref_obj = ref;

	new_inst.scale.elem[0][0] = 1;
	new_inst.scale.elem[0][1] = 0;
	new_inst.scale.elem[0][2] = 0;
	new_inst.scale.elem[0][3] = 0;
	new_inst.scale.elem[1][0] = 0;
	new_inst.scale.elem[1][1] = 1;
	new_inst.scale.elem[1][2] = 0;
	new_inst.scale.elem[1][3] = 0;
	new_inst.scale.elem[2][0] = 0;
	new_inst.scale.elem[2][1] = 0;
	new_inst.scale.elem[2][2] = 1;
	new_inst.scale.elem[2][3] = 0;
	new_inst.scale.elem[3][0] = 0;
	new_inst.scale.elem[3][1] = 0;
	new_inst.scale.elem[3][2] = 0;
	new_inst.scale.elem[3][3] = 1;

	new_inst.rotation.elem[0][0] = 1;
	new_inst.rotation.elem[0][1] = 0;
	new_inst.rotation.elem[0][2] = 0;
	new_inst.rotation.elem[0][3] = 0;
	new_inst.rotation.elem[1][0] = 0;
	new_inst.rotation.elem[1][1] = 1;
	new_inst.rotation.elem[1][2] = 0;
	new_inst.rotation.elem[1][3] = 0;
	new_inst.rotation.elem[2][0] = 0;
	new_inst.rotation.elem[2][1] = 0;
	new_inst.rotation.elem[2][2] = 1;
	new_inst.rotation.elem[2][3] = 0;
	new_inst.rotation.elem[3][0] = 0;
	new_inst.rotation.elem[3][1] = 0;
	new_inst.rotation.elem[3][2] = 0;
	new_inst.rotation.elem[3][3] = 1;

	new_inst.translate.elem[0][0] = 1;
	new_inst.translate.elem[0][1] = 0;
	new_inst.translate.elem[0][2] = 0;
	new_inst.translate.elem[0][3] = -4;
	new_inst.translate.elem[1][0] = 0;
	new_inst.translate.elem[1][1] = 1;
	new_inst.translate.elem[1][2] = 0;
	new_inst.translate.elem[1][3] = -7;
	new_inst.translate.elem[2][0] = 0;
	new_inst.translate.elem[2][1] = 0;
	new_inst.translate.elem[2][2] = 1;
	new_inst.translate.elem[2][3] = 5;
	new_inst.translate.elem[3][0] = 0;
	new_inst.translate.elem[3][1] = 0;
	new_inst.translate.elem[3][2] = 0;
	new_inst.translate.elem[3][3] = 1;

	new_inst.x_ang = 0;
	new_inst.y_ang = 0;

	return (new_inst);
}

t_camera	initialize_camera(float d)
{
	t_camera cam;

	cam.rotation.elem[0][0] = 1;
	cam.rotation.elem[0][1] = 0;
	cam.rotation.elem[0][2] = 0;
	cam.rotation.elem[0][3] = 0;
	cam.rotation.elem[1][0] = 0;
	cam.rotation.elem[1][1] = 1;
	cam.rotation.elem[1][2] = 0;
	cam.rotation.elem[1][3] = 0;
	cam.rotation.elem[2][0] = 0;
	cam.rotation.elem[2][1] = 0;
	cam.rotation.elem[2][2] = 1;
	cam.rotation.elem[2][3] = 0;
	cam.rotation.elem[3][0] = 0;
	cam.rotation.elem[3][1] = 0;
	cam.rotation.elem[3][2] = 0;
	cam.rotation.elem[3][3] = 1;

	cam.translation.elem[0][0] = 0;
	cam.translation.elem[0][1] = 0;
	cam.translation.elem[0][2] = 0;
	cam.translation.elem[0][3] = 1;
	cam.translation.elem[1][0] = 0;
	cam.translation.elem[1][1] = 0;
	cam.translation.elem[1][2] = 0;
	cam.translation.elem[1][3] = 1;
	cam.translation.elem[2][0] = 0;
	cam.translation.elem[2][1] = 0;
	cam.translation.elem[2][2] = 0;
	cam.translation.elem[2][3] = 1;
	cam.translation.elem[3][0] = 0;
	cam.translation.elem[3][1] = 0;
	cam.translation.elem[3][2] = 0;
	cam.translation.elem[3][3] = 1;

	cam.projection.elem[0][0] = d;
	cam.projection.elem[0][1] = 0;
	cam.projection.elem[0][2] = 0;
	cam.projection.elem[0][3] = 0;
	cam.projection.elem[1][0] = 0;
	cam.projection.elem[1][1] = d;
	cam.projection.elem[1][2] = 0;
	cam.projection.elem[1][3] = 0;
	cam.projection.elem[2][0] = 0;
	cam.projection.elem[2][1] = 0;
	cam.projection.elem[2][2] = 1;
	cam.projection.elem[2][3] = 0;
	cam.projection.elem[3][0] = 1;
	cam.projection.elem[3][1] = 1;
	cam.projection.elem[3][2] = 1;
	cam.projection.elem[3][3] = 1;


	return (cam);
}

t_pt2		make_pt2_from_v3(t_vec3 vec)
{
	t_pt2 pt2;
	float x;
	float y;

	vec.elem[0] = vec.elem[0] / vec.elem[3];
	vec.elem[1] = vec.elem[1] / vec.elem[3];
	vec.elem[2] = vec.elem[2] / vec.elem[3];
	x = vec.elem[0] / vec.elem[2];
	y = vec.elem[1] / vec.elem[2];
	pt2.x = (x * (WIDTH / 2) / 2) + WIDTH / 2;
	pt2.y = (y * (HIEGHT/ 2) / 2 * (float)((float)WIDTH / (float)HIEGHT)) + HIEGHT / 2;
	pt2.z1 = 1 / vec.elem[2];
	return (pt2);
}

void 		put_pixel(int x, int y, int color, t_data *data)
{
	if (x >= WIDTH || x < 0 || y >= HIEGHT || y < 0)
		return;
	((int*)(data->img_data))[x + (y * WIDTH)] = color;
}