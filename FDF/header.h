/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 16:16:54 by mcamila           #+#    #+#             */
/*   Updated: 2020/01/20 13:25:42 by mcamila          ###   ########.fr       */
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

typedef struct	s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	int		mouse_bool;
	int			x;
	int			y;
	int			x1;
	int			y1;
}				t_data;

void	go_away(t_data *data);
void	draw_line(int x0, int y0, int x1, int y1, t_data *data, int color);
void	draw_tri(int x0, int y0, int x1, int y1, int x2, int y2, t_data *data);

#endif /* HEADER_H */