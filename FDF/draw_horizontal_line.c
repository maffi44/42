/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_horisontal_line.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 16:22:08 by mcamila           #+#    #+#             */
/*   Updated: 2020/02/21 17:19:44 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	swap_sc_pt(t_screen_pt *p1, t_screen_pt *p2)
{
	t_screen_pt temp;

	temp = *p1;
	*p1 = *p2;
	*p2 = temp;
}

void draw_horizontal_line(t_screen_pt p1, t_screen_pt p2, int y, t_data *data)
{
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

	if (p1.x == p2.x)
		return ;
	if (p1.x > p2.x)
		swap_sc_pt(&p1, &p2);
	h = p1.h;
	a = (p2.h - p1.h) / (p2.x - p1.x);
	Z0 = p1.z;
	ZB = (p2.z - p1.z) / (p2.x - p1.x);
	t_color col;
	col.ARGB = 0;
	C_R = p1.col.colors[2];
	C_G = p1.col.colors[1];
	C_B = p1.col.colors[0];
	cb_r = (float)(p2.col.colors[2] - p1.col.colors[2]) / (p2.x - p1.x);
	cb_g = (float)(p2.col.colors[1] - p1.col.colors[1]) / (p2.x - p1.x);
	cb_b = (float)(p2.col.colors[0] - p1.col.colors[0]) / (p2.x - p1.x);
	while (p1.x <= p2.x)
	{
		if ((p1.x >= 0 && (int)p1.x < WIDTH) && (y >= 0 && y < HIEGHT))
		{
			if (Z0 >= data->zbuff[((int)p1.x + (y * WIDTH)) - 1])
			{
				data->zbuff[((int)p1.x + (y * (WIDTH))) - 1] = Z0;
				col.colors[2] = (char)(C_R * data->disco);
				col.colors[1] = (char)(C_G * data->disco);
				col.colors[0] = (char)(C_B * data->disco);
				col.colors[2] = (char)(col.colors[2] * h);
				col.colors[1] = (char)(col.colors[1] * h);
				col.colors[0] = (char)(col.colors[0] * h);
				put_pixel((int)p1.x, y, col.ARGB, data);
			}
		}
		C_R += cb_r;
		C_G += cb_g;
		C_B += cb_b;
		h += a;
		p1.x++;
		Z0 += ZB;
	}
}

//draw_hor_line(float x0, float x1, int y, t_data *data, float h0, float h1, float zb1, float zb2, t_color col0, t_color col1);

void draw_hor_line(t_draw *s, int y, t_data *data)
{
	t_screen_pt p1;
	t_screen_pt p2;

	p1.x = s->X1;
	p1.h = s->H1;
	p1.z = s->ZB1;
	p1.col = s->col1;
	p2.x = s->X2;
	p2.h = s->H2;
	p2.z = s->ZB2;
	p2.col = s->col2;

	draw_horizontal_line(p1, p2, y, data);
}