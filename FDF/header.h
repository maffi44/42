/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 16:16:54 by mcamila           #+#    #+#             */
/*   Updated: 2020/01/30 12:47:19 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "/Users/mcamila/MyProjects/42/42/libft/libft.h"
#include "/Users/mcamila/MyProjects/42/42/MinilibX/minilibx_macos/mlx.h"
#include <math.h>
#include "structs.h"
#include "matrix.h"
#include "functions.h"

# define HIEGHT	500
# define WIDTH	500

void	go_away(t_data *data);
void	draw_line(int x0, int y0, int x1, int y1, t_data *data, int color);
void	draw_tri(t_pt2 p0, t_pt2 p1, t_pt2 p2, double h0, double h1, double h2, t_data *data);
void	render_frame(t_inst_obj *objects, int  num_of_obj, t_data *data);

#endif /* HEADER_H */