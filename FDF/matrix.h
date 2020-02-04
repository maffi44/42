/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 01:43:15 by mcamila           #+#    #+#             */
/*   Updated: 2020/02/04 17:18:10 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

typedef struct	s_matrix
{
	double 		elem[4][4];
	int			i;
}				t_matrix;

typedef struct	s_vec3
{
	double		elem[4];
}				t_vec3;


t_matrix	matrix_mult(t_matrix A, t_matrix B);
t_vec3	vec3_transform(t_matrix matrix, t_vec3 vec);
t_vec3	make_vertex(double x, double y, double z);
t_matrix	make_rotation_matrix(double x_rot, double y_rot);
float		vec_scalar_mult(t_vec3 v1, t_vec3 v2);
t_vec3		vec_mult(t_vec3 v1, t_vec3 v2);
t_vec3		vec_divide(t_vec3 to, t_vec3 from);
t_vec3		normalize_vec(t_vec3 vec);
float		vec_length(t_vec3 vec);

#endif /* MATRIX_H */