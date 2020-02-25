/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 05:58:02 by mcamila           #+#    #+#             */
/*   Updated: 2020/02/24 19:27:52 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

inline t_vec3		vec_mult(t_vec3 v1, t_vec3 v2)
{
	t_vec3 res;

	if (v1.elem[3] != 1 || v1.elem[3] != 0)
	{
		v1.elem[0] = v1.elem[0] / v1.elem[3];
		v1.elem[1] = v1.elem[1] / v1.elem[3];
		v1.elem[2] = v1.elem[2] / v1.elem[3];
	}
	if (v2.elem[3] != 1 || v1.elem[3] != 0)
	{
		v2.elem[0] = v2.elem[0] / v2.elem[3];
		v2.elem[1] = v2.elem[1] / v2.elem[3];
		v2.elem[2] = v2.elem[2] / v2.elem[3];
	}
	res.elem[0] = v1.elem[2] * v2.elem[1] - v1.elem[1] * v2.elem[2];
	res.elem[1] = v1.elem[0] * v2.elem[2] - v1.elem[2] * v2.elem[0];
	res.elem[2] = v1.elem[1] * v2.elem[0] - v1.elem[0] * v2.elem[1];
	return (res);
}

inline float		vec_scalar_mult(t_vec3 v1, t_vec3 v2)
{
	return ((v1.elem[0] * v2.elem[0])
			+ (v1.elem[1] * v2.elem[1])
			+ (v1.elem[2] * v2.elem[2]));
}

inline t_vec3		make_vertex(float x, float y, float z, unsigned int color)
{
	t_vec3	vertex;

	vertex.elem[0] = x;
	vertex.elem[1] = y;
	vertex.elem[2] = z;
	vertex.elem[3] = 1;
	vertex.color = color;
	return (vertex);
}

inline t_matrix		make_transform_matrix(t_inst_obj obj)
{
	t_matrix transform;

	transform = matrix_mult(obj.rotation, obj.scale);
	transform = matrix_mult(transform, obj.translate);
	return (transform);
}

inline t_matrix		make_rotation_matrix(float x_rot, float y_rot)
{
	t_matrix	mat;

	mat.elem[0][0] = cosf(y_rot);
	mat.elem[0][1] = sinf(y_rot) * sinf(x_rot);
	mat.elem[0][2] = sinf(y_rot) * cosf(x_rot);
	mat.elem[0][3] = 0;
	mat.elem[1][0] = 0;
	mat.elem[1][1] = cosf(x_rot);
	mat.elem[1][2] = -sinf(x_rot);
	mat.elem[1][3] = 0;
	mat.elem[2][0] = -sinf(y_rot);
	mat.elem[2][1] = sinf(x_rot) * cosf(y_rot);
	mat.elem[2][2] = cosf(x_rot) * cosf(y_rot);
	mat.elem[2][3] = 0;
	mat.elem[3][0] = 0;
	mat.elem[3][1] = 0;
	mat.elem[3][2] = 0;
	mat.elem[3][3] = 1;
	return (mat);
}
