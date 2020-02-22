/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_horizontal_line.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 01:14:36 by mcamila           #+#    #+#             */
/*   Updated: 2020/02/22 03:16:26 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void draw_hor_line(t_draw s, int y, t_data *data, t_color col0, t_color col1)
{
	float x;
	float h;
	float a;
	float Z0;
	float ZB;
	float C_R;
	float C_G;
	float C_B;
	float cb_r;
	float cb_g;
	float cb_b;

	if ((s.X1) == (s.X2))
		return ;
	if ((s.X1) > (s.X2))
	{
		swap_f(&(s.X1), &(s.X2));
		swap_f(&(s.H1), &(s.H2));
		swap_f(&(s.ZB1), &(s.ZB2));
		swap_colors(&col0, &col1);
	}
	x = (s.X1);
	h = (s.H1);
	a = ((s.H2) - (s.H1)) / ((s.X2) - (s.X1));
	Z0 = (s.ZB1);
	ZB = ((s.ZB2 - (s.ZB1)) / ((s.X2) - (s.X1)));
	t_color col;
	col.ARGB = 0;
	C_R = col0.colors[2];
	C_G = col0.colors[1];
	C_B = col0.colors[0];
	cb_r = (float)(col1.colors[2] - col0.colors[2]) / ((s.X2) - (s.X1));
	cb_g = (float)(col1.colors[1] - col0.colors[1]) / ((s.X2) - (s.X1));
	cb_b = (float)(col1.colors[0] - col0.colors[0]) / ((s.X2) - (s.X1));
	while (x <= (s.X2))
	{
		if ((x >= 0 && (int)x < WIDTH) && (y >= 0 && y < HIEGHT)
			&& (Z0 >= data->zbuff[((int)x + (y * WIDTH)) - 1]))
		{
			data->zbuff[((int)x + (y * (WIDTH))) - 1] = Z0;
			col.colors[2] = (char)(C_R * data->disco);
			col.colors[1] = (char)(C_G * data->disco);
			col.colors[0] = (char)(C_B * data->disco);
			col.colors[2] = (char)(col.colors[2] * h);
			col.colors[1] = (char)(col.colors[1] * h);
			col.colors[0] = (char)(col.colors[0] * h);
			put_pixel((int)x, y, col.ARGB, data);
		}
		C_R += cb_r;
		C_G += cb_g;
		C_B += cb_b;
		h += a;
		x++;
		Z0 += ZB;
	}
}