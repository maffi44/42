/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 12:42:03 by mcamila           #+#    #+#             */
/*   Updated: 2020/02/22 04:43:11 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	make_sc_matrix(t_inst_obj *new_inst, float x_sc, float y_sc, float z_sc)
{
	new_inst->scale.elem[0][0] = x_sc;
	new_inst->scale.elem[0][1] = 0;
	new_inst->scale.elem[0][2] = 0;
	new_inst->scale.elem[0][3] = 0;
	new_inst->scale.elem[1][0] = 0;
	new_inst->scale.elem[1][1] = y_sc;
	new_inst->scale.elem[1][2] = 0;
	new_inst->scale.elem[1][3] = 0;
	new_inst->scale.elem[2][0] = 0;
	new_inst->scale.elem[2][1] = 0;
	new_inst->scale.elem[2][2] = z_sc;
	new_inst->scale.elem[2][3] = 0;
	new_inst->scale.elem[3][0] = 0;
	new_inst->scale.elem[3][1] = 0;
	new_inst->scale.elem[3][2] = 0;
	new_inst->scale.elem[3][3] = 1;
}

void	make_rot_matrix(t_inst_obj *new_inst)
{
	new_inst->rotation.elem[0][0] = 1;
	new_inst->rotation.elem[0][1] = 0;
	new_inst->rotation.elem[0][2] = 0;
	new_inst->rotation.elem[0][3] = 0;
	new_inst->rotation.elem[1][0] = 0;
	new_inst->rotation.elem[1][1] = 1;
	new_inst->rotation.elem[1][2] = 0;
	new_inst->rotation.elem[1][3] = 0;
	new_inst->rotation.elem[2][0] = 0;
	new_inst->rotation.elem[2][1] = 0;
	new_inst->rotation.elem[2][2] = 1;
	new_inst->rotation.elem[2][3] = 0;
	new_inst->rotation.elem[3][0] = 0;
	new_inst->rotation.elem[3][1] = 0;
	new_inst->rotation.elem[3][2] = 0;
	new_inst->rotation.elem[3][3] = 1;
}

void	make_tr_matrix(t_inst_obj *new_inst)
{
	new_inst->translate.elem[0][0] = 1;
	new_inst->translate.elem[0][1] = 0;
	new_inst->translate.elem[0][2] = 0;
	new_inst->translate.elem[0][3] = 0;
	new_inst->translate.elem[1][0] = 0;
	new_inst->translate.elem[1][1] = 1;
	new_inst->translate.elem[1][2] = 0;
	new_inst->translate.elem[1][3] = 0;
	new_inst->translate.elem[2][0] = 0;
	new_inst->translate.elem[2][1] = 0;
	new_inst->translate.elem[2][2] = 1;
	new_inst->translate.elem[2][3] = 5;
	new_inst->translate.elem[3][0] = 0;
	new_inst->translate.elem[3][1] = 0;
	new_inst->translate.elem[3][2] = 0;
	new_inst->translate.elem[3][3] = 1;
}

t_inst_obj	*make_obj_inst(t_ref_obj *ref, float x_sc, float y_sc, float z_sc)
{
	t_inst_obj	*new_inst;

	new_inst = (t_inst_obj*)malloc(sizeof(t_inst_obj));
	new_inst->ref_obj = ref;
	make_sc_matrix(new_inst, x_sc, y_sc, z_sc);
	make_rot_matrix(new_inst);
	make_tr_matrix(new_inst);
	new_inst->x_ang = 0;
	new_inst->y_ang = 0;
	return (new_inst);
}

void		initialize_rotation(t_camera *cam)
{
	cam->rotation.elem[0][0] = 1;
	cam->rotation.elem[0][1] = 0;
	cam->rotation.elem[0][2] = 0;
	cam->rotation.elem[0][3] = 0;
	cam->rotation.elem[1][0] = 0;
	cam->rotation.elem[1][1] = 1;
	cam->rotation.elem[1][2] = 0;
	cam->rotation.elem[1][3] = 0;
	cam->rotation.elem[2][0] = 0;
	cam->rotation.elem[2][1] = 0;
	cam->rotation.elem[2][2] = 1;
	cam->rotation.elem[2][3] = 0;
	cam->rotation.elem[3][0] = 0;
	cam->rotation.elem[3][1] = 0;
	cam->rotation.elem[3][2] = 0;
	cam->rotation.elem[3][3] = 1;
}

void		initialize_translation(t_camera *cam)
{
	cam->translation.elem[0][0] = 0;
	cam->translation.elem[0][1] = 0;
	cam->translation.elem[0][2] = 0;
	cam->translation.elem[0][3] = 1;
	cam->translation.elem[1][0] = 0;
	cam->translation.elem[1][1] = 0;
	cam->translation.elem[1][2] = 0;
	cam->translation.elem[1][3] = 1;
	cam->translation.elem[2][0] = 0;
	cam->translation.elem[2][1] = 0;
	cam->translation.elem[2][2] = 0;
	cam->translation.elem[2][3] = 1;
	cam->translation.elem[3][0] = 0;
	cam->translation.elem[3][1] = 0;
	cam->translation.elem[3][2] = 0;
	cam->translation.elem[3][3] = 1;
}

void		initialize_projection(t_camera *cam, float d)
{
	cam->projection.elem[0][0] = d;
	cam->projection.elem[0][1] = 0;
	cam->projection.elem[0][2] = 0;
	cam->projection.elem[0][3] = 0;
	cam->projection.elem[1][0] = 0;
	cam->projection.elem[1][1] = d;
	cam->projection.elem[1][2] = 0;
	cam->projection.elem[1][3] = 0;
	cam->projection.elem[2][0] = 0;
	cam->projection.elem[2][1] = 0;
	cam->projection.elem[2][2] = 1;
	cam->projection.elem[2][3] = 0;
	cam->projection.elem[3][0] = 1;
	cam->projection.elem[3][1] = 1;
	cam->projection.elem[3][2] = 1;
	cam->projection.elem[3][3] = 1;
}

t_camera	initialize_camera(float d)
{
	t_camera cam;

	initialize_rotation(&cam);
	initialize_translation(&cam);
	initialize_projection(&cam, d);
	return (cam);
}

inline t_pt2		make_pt2_from_v3(t_vec3 vec, float d)
{
	t_pt2 pt2;
	float x;
	float y;

	vec.elem[0] = vec.elem[0] / vec.elem[3];
	vec.elem[1] = vec.elem[1] / vec.elem[3];
	vec.elem[2] = vec.elem[2] / vec.elem[3];
	x = vec.elem[0] * d / vec.elem[2];
	y = vec.elem[1] * d / vec.elem[2];
	pt2.x = (x * (WIDTH / 2) / 2) + WIDTH / 2;
	pt2.y = (y * (HIEGHT / 2) / 2 * (float)((float)WIDTH / (float)HIEGHT))
			+ HIEGHT / 2;
	pt2.z1 = 1 / vec.elem[2];
	return (pt2);
}

inline void		put_pixel(int x, int y, int color, t_data *data)
{
	if (x >= WIDTH || x < 0 || y >= HIEGHT || y < 0)
		return ;
	((int*)(data->img_data))[x + (y * WIDTH)] = color;
}
