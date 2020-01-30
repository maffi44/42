/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 17:06:33 by mcamila           #+#    #+#             */
/*   Updated: 2020/01/30 06:08:30 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_matrix	matrix_mult(t_matrix A, t_matrix B)
{
	t_matrix C;
	int i;
	int j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			C.elem[i][j] = A.elem[0][i] * B.elem[j][0] +  A.elem[1][i] * B.elem[j][1] +
						   A.elem[2][i] * B.elem[j][2] +  A.elem[3][i] * B.elem[j][3];
			j++;
		}
		i++;
	}
	return (C);
}

t_vec3	vec3_transform(t_matrix matrix, t_vec3 vec)
{
	t_vec3 new_vec;
	int i;

	i = 0;
	while (i < 4)
	{
		new_vec.elem[i] = vec.elem[0] * matrix.elem[0][i] + vec.elem[1] * matrix.elem[1][i] +
						  vec.elem[2] * matrix.elem[2][i] + vec.elem[3] * matrix.elem[3][i];
		i++;
	}
	return (new_vec);
}

t_vec3	make_vertex(double x, double y, double z)
{
	t_vec3	vertex;

	vertex.elem[0] = x;
	vertex.elem[1] = y;
	vertex.elem[2] = z;
	vertex.elem[3] = 1;
	return (vertex);
}

t_matrix	make_transform_matrix(t_camera cam, t_inst_obj obj)
{
	t_matrix transform;

	transform = matrix_mult(obj.scale, obj.rotation);
	transform = matrix_mult(transform, obj.translate);
//	transform = matrix_mult(transform, cam.projection);

//	transform = matrix_mult(
//			cam.projection,
//			matrix_mult(matrix_mult(obj.scale,obj.rotation), obj.translate));
	return (transform);
}