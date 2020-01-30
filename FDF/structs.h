/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 19:17:48 by mcamila           #+#    #+#             */
/*   Updated: 2020/01/30 03:02:08 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

#include "matrix.h"

typedef struct	s_pt2
{
	int			x;
	int			y;
}				t_pt2;

typedef struct	s_tri
{
	int	pt[3];
}				t_tri;

typedef struct	s_ref_obj
{
	t_vec3		*vertex;
	t_tri		*tri;
	int			num_of_pts;
	int			num_of_tris;
}				t_ref_obj;

typedef struct	s_inst_obj
{
	t_ref_obj	*ref_obj;
	t_matrix	scale;
	t_matrix	rotation;
	t_matrix	translate;
	t_matrix	transform;
}				t_inst_obj;

typedef struct	s_camera
{
	t_matrix	transform;
	t_matrix	rotation;
	t_matrix	translation;
	t_matrix	projection;
	float 		d;
}				t_camera;

typedef struct	s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_inst_obj	*obj_inst;
	t_camera	camera;
	int			x;
	int			y;
	int			x1;
	int			y1;
	int 		mouse_bool;
}				t_data;

#endif