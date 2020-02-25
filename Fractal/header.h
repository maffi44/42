/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 16:16:54 by mcamila           #+#    #+#             */
/*   Updated: 2020/02/26 02:29:50 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# define CL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include "libft/libft.h"
# include "MinilibX/minilibx_macos/mlx.h"
# include "structs.h"
# include "fractol.h"

void	go_away(t_data *data);
int		key_press(int key, t_data *data);
int		key_release(int key, t_data *data);
int		mouse_press(int button, int x, int y, t_data *data);
int		x_press(void *data);
void	put_pixel(int x, int y, int color, t_data *data);
int		ft_render(t_data *data);
t_color	color_loop(unsigned int speed, t_color c);
int		color_add_6(t_color *c);
int		color_add_5(t_color *c);
int		color_add_4(t_color *c);
int		color_add_3(t_color *c);
int		color_add_2(t_color *c);
int		color_add_1(t_color *c);
int		color_add_11(t_color *c);
int		color_add_22(t_color *c);
int		color_add_33(t_color *c);

# define HIEGHT	1600
# define WIDTH	1600

#endif
