/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 19:17:48 by mcamila           #+#    #+#             */
/*   Updated: 2020/02/21 16:15:01 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

#include "header.h"
#include "matrix.h"

typedef union		u_color
{
	unsigned int 	ARGB;
	unsigned char	colors[4];
}					t_color;

typedef struct	s_pt2
{
	float		x;
	float		y;
	float 		z1;
	t_color		color;
	float 		light;
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
	float		x_ang;
	float 		y_ang;
}				t_inst_obj;

typedef struct	s_camera
{
	t_matrix	transform;
	t_matrix	rotation;
	t_matrix	translation;
	t_matrix	projection;
	float 		d;
}				t_camera;


typedef struct 	s_maps
{
	char		**line;
	char		*big_line;
	char		*temp;
	char		***big_map;
	int			**map;
}				t_maps;

typedef struct		s_screen_tri
{
	t_pt2	pt1;
	t_pt2	pt2;
	t_pt2	pt3;
}					t_sc_tri;

typedef struct		s_space_tri
{
	t_vec3	normal;
	t_vec3	vertex1;
	t_vec3	vertex2;
	t_vec3	vertex3;
	t_vec3	light_vector1;
	t_vec3	light_vector2;
	t_vec3	light_vector3;
	t_vec3	edge1;
	t_vec3	edge2;
	char 	bool;
}					t_sp_tri;

typedef struct	s_draw
{
	float		a1;
	float		a2;
	float		X1;
	float		X2;
	float		H1;
	float		H2;
	float		b1;
	float		b2;
	float		ZB1;
	float		ZB2;
	float		zb1;
	float		zb2;
	float		C_R1;
	float		C_G1;
	float		C_B1;
	float		C_R2;
	float		C_G2;
	float		C_B2;
	float		cb_r1;
	float		cb_g1;
	float		cb_b1;
	float		cb_r2;
	float		cb_g2;
	float		cb_b2;
	t_color		col1;
	t_color		col2;
}				t_draw;

typedef struct		s_screen_pt
{
	float 			x;
	float 			h;
	float 			z;
	t_color			col;
}					t_screen_pt;

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
	float 		d;
	t_camera	camera;
	t_vec3		dir_light;
	int			x;
	int			y;
	int			R_bool;
	int 		mouse_bool;
	int 		Q_bool;
	int 		H_bool;
	int 		F_bool;
	float		disco;
}				t_data;

#endif