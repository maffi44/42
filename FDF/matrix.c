/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   by: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   created: 2020/01/29 17:06:33 by mcamila           #+#    #+#             */
/*   Updated: 2020/02/19 14:06:13 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

inline t_matrix		matrix_mult(t_matrix a, t_matrix b)
{
	t_matrix	c;
	int			i;
	int			j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			c.elem[i][j] = a.elem[0][i] * b.elem[j][0]
					+ a.elem[1][i] * b.elem[j][1]
					+ a.elem[2][i] * b.elem[j][2]
					+ a.elem[3][i] * b.elem[j][3];
			j++;
		}
		i++;
	}
	return (c);
}

inline t_vec3		vec3_transform(t_matrix matrix, t_vec3 vec)
{
	t_vec3	new_vec;
	int		i;

	i = 0;
	while (i < 4)
	{
		new_vec.elem[i] = vec.elem[0] * matrix.elem[0][i]
				+ vec.elem[1] * matrix.elem[1][i]
				+ vec.elem[2] * matrix.elem[2][i]
				+ vec.elem[3] * matrix.elem[3][i];
		i++;
	}
	return (new_vec);
}

inline t_vec3		vec_divide(t_vec3 from, t_vec3 to)
{
	t_vec3 res;

	if (to.elem[3] != 1 || to.elem[3] != 0)
	{
		to.elem[0] = to.elem[0] / to.elem[3];
		to.elem[1] = to.elem[1] / to.elem[3];
		to.elem[2] = to.elem[2] / to.elem[3];
	}
	if (from.elem[3] != 1 || from.elem[3] != 0)
	{
		from.elem[0] = from.elem[0] / from.elem[3];
		from.elem[1] = from.elem[1] / from.elem[3];
		from.elem[2] = from.elem[2] / from.elem[3];
	}
	res.elem[0] = to.elem[0] - from.elem[0];
	res.elem[1] = to.elem[1] - from.elem[1];
	res.elem[2] = to.elem[2] - from.elem[2];
	res.elem[3] = 1;
	return (res);
}

inline float		vec_length(t_vec3 vec)
{
	if (vec.elem[3] != 1 || vec.elem[3] != 0)
	{
		vec.elem[0] = vec.elem[0] / vec.elem[3];
		vec.elem[1] = vec.elem[1] / vec.elem[3];
		vec.elem[2] = vec.elem[2] / vec.elem[3];
	}
	return (sqrtf(vec.elem[0] * vec.elem[0]
	+ vec.elem[1] * vec.elem[1]
	+ vec.elem[2] * vec.elem[2]));
}

inline t_vec3		normalize_vec(t_vec3 vec)
{
	float len;

	if (vec.elem[3] != 1 || vec.elem[3] != 0)
	{
		vec.elem[0] = vec.elem[0] / vec.elem[3];
		vec.elem[1] = vec.elem[1] / vec.elem[3];
		vec.elem[2] = vec.elem[2] / vec.elem[3];
	}
	len = vec_length(vec);
	vec.elem[0] = vec.elem[0] / len;
	vec.elem[1] = vec.elem[1] / len;
	vec.elem[2] = vec.elem[2] / len;
	return (vec);
}

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

inline t_matrix		make_transform_matrix(t_camera cam, t_inst_obj obj)
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
