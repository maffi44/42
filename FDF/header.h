/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 16:16:54 by mcamila           #+#    #+#             */
/*   Updated: 2020/02/18 19:37:06 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "libft/libft.h"
#include "MinilibX/minilibx_macos/mlx.h"
#include "map_parser.h"
#include "structs.h"
#include "matrix.h"
#include "functions.h"

# define HIEGHT	1080
# define WIDTH	1920

void	go_away(t_data *data);
void	draw_line(int x0, int y0, int x1, int y1, t_data *data, int color);
void	draw_tri(t_pt2 p0, t_pt2 p1, t_pt2 p2,  t_data *data);
void	render_frame(t_inst_obj *objects, int  num_of_obj, t_data *data);

void swap_f(float *a, float *b);
float absolute(float x);
void swap_colors(t_color *a, t_color *b);
void swap(int* a , int*b);
void swap_2pt(t_pt2 *a, t_pt2 *b);


#endif /* HEADER_H */