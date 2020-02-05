/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 19:17:48 by mcamila           #+#    #+#             */
/*   Updated: 2020/01/30 13:18:20 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

#include "header.h"
#include "matrix.h"

typedef struct	s_pt2
{
	double		x;
	double		y;
	double 		z1;
}				t_pt2;

typedef struct	s_tri
{
	int	pt[3];
}				t_tri;

typedef	struct	s_normal
{
	t_vec3		nor[3];
}				t_normal;

typedef struct	s_ref_obj
{
	t_vec3		*vertex;
	t_tri		*tri;
	t_normal	*normals;
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
	double		x_ang;
	double 		y_ang;
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
	void		*img_ptr;
	void		*img_data;
	float 		*zbuff;
	int 		img_line;
	int 		bpp;
	int 		endian;
	t_inst_obj	*obj_inst;
	t_camera	camera;
	t_vec3		dir_light;
	int			x;
	int			y;
	int			R_bool;
	int 		mouse_bool;
}				t_data;

#endif