/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 19:17:48 by mcamila           #+#    #+#             */
/*   Updated: 2020/02/26 07:44:45 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "header.h"

typedef union			u_color
{
	unsigned int		argb;
	unsigned char		colors[4];
}						t_color;

typedef struct			s_opencl
{
	int					ret;
	cl_platform_id		pl_id;
	cl_device_id		dev_id;
	cl_context			ctxt;
	cl_command_queue	cmd_queue;
	cl_program			program;
	cl_kernel			kernel;
	cl_uint				ret_num_platforms;
	cl_uint				ret_num_devices;
	char				*source_str;
	size_t				source_size;
	cl_mem				cl_data;
	size_t				data_size;
	cl_int				*res;
}						t_opencl;

typedef	struct			s_params
{
	int					img_line;
	int					bpp;
	int					endian;
	int					x;
	int					y;
	float				k_re;
	float				k_im;
	int					fract;
	float				sc;
	int					max_iteration;
	float				re_off;
	float				im_off;
	int					m_bool;
	int					sc_bool;
	t_color				col;
	int					jul_bool;
}						t_params;

typedef struct			s_data
{
	void				*mlx_ptr;
	void				*win_ptr;
	void				*img_ptr;
	void				*img_data;
	t_params			p;
	t_opencl			*opencl;
}						t_data;

#endif
