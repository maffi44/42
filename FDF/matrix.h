/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 01:43:15 by mcamila           #+#    #+#             */
/*   Updated: 2020/01/30 02:54:22 by mcamila          ###   ########.fr       */
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

#endif /* MATRIX_H */