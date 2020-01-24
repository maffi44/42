/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 16:16:54 by mcamila           #+#    #+#             */
/*   Updated: 2020/01/24 21:02:41 by mcamila          ###   ########.fr       */
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

# define HIEGHT	1080
# define WIDTH	1920

typedef struct	s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			mouse_bool;
	int			x;
	int			y;
	int			x1;
	int			y1;
}				t_data;

void	go_away(t_data *data);
void	draw_line(int x0, int y0, int x1, int y1, t_data *data, int color);
void	draw_tri(int x0, int y0, double h0, int x1, int y1, double h1, int x2, int y2, double h2, t_data *data);
void	render_frame(t_3d_obj *objects, int  num_of_obj, t_data *data);

#endif /* HEADER_H */