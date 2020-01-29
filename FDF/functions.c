/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 12:42:03 by mcamila           #+#    #+#             */
/*   Updated: 2020/01/30 00:17:31 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_pt3	pt3_add(t_pt3 pt1, t_pt3 pt2)
{
	pt1.x += pt2.x;
	pt1.y += pt2.y;
	pt1.z += pt2.z;
	return (pt1);
}

t_inst_obj	make_obj_inst(t_ref_obj *ref)
{
	t_inst_obj	new_inst;

	new_inst.ref_obj = ref;
	new_inst.scale = {{1, 0, 0, 0,}, {0, 1, 0, 0}, {0, 0, 1, 0}, (0, 0, 0, 1)};
	new_inst.rotation = {{1, 0, 0, 0,}, {0, 1, 0, 0}, {0, 0, 1, 0}, (0, 0, 0, 1)};
	new_inst.translate = {{0, 0, 0, 1,}, {0, 0, 0, 1}, {0, 0, 0, 1}, (0, 0, 0, 1)};
}

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
			C.elem[i][j] = A.elem[i][0] * B.elem[0][j] +  A.elem[i][1] * B.elem[1][j] +
					A.elem[i][2] * B.elem[2][j] +  A.elem[3][0] * B.elem[3][j];
			j++;
		}
		i++;
	}
	return (C);
}