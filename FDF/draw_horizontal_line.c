/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_horisontal_line.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 16:22:08 by mcamila           #+#    #+#             */
/*   Updated: 2020/02/21 21:35:46 by mcamila          ###   ########.fr       */
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

void draw_horizontal_line(t_screen_pt *p1, t_screen_pt *p2, int y, t_data *data);

inline void draw_horizontal_line(t_screen_pt *p1, t_screen_pt *p2, int y, t_data *data)
{
	float a;
	float ZB;
	float cb_r;
	float cb_g;
	float cb_b;

	if (p1->x == p2->x)
		return ;
	if (p1->x > p2->x)
		swap_sc_pt(p1, p2);
	a = (p2->h - p1->h) / (p2->x - p1->x);
	ZB = (p2->z - p1->z) / (p2->x - p1->x);
	t_color col;
	col.ARGB = 0;
	cb_r = (float)(p2->col.colors[2] - p1->col.colors[2]) / (p2->x - p1->x);
	cb_g = (float)(p2->col.colors[1] - p1->col.colors[1]) / (p2->x - p1->x);
	cb_b = (float)(p2->col.colors[0] - p1->col.colors[0]) / (p2->x - p1->x);
	while (p1->x <= p2->x)
	{
		if ((p1->x >= 0 && (int)p1->x < WIDTH) && (y >= 0 && y < HIEGHT))
		{
			if (p1->z >= data->zbuff[((int)p1->x + (y * WIDTH)) - 1])
			{
				data->zbuff[((int)p1->x + (y * (WIDTH))) - 1] = p1->z;
//				col.colors[2] = (char)((p1->col.colors[2] * data->disco) * p1->h);
//				col.colors[1] = (char)((p1->col.colors[1] * data->disco) * p1->h);
//				col.colors[0] = (char)((p1->col.colors[0] * data->disco) * p1->h);

				col.colors[2] = (char)((float)(p1->col.colors[2]) * p1->h);
				col.colors[1] = (char)((float)(p1->col.colors[1]) * p1->h);
				col.colors[0] = (char)((float)(p1->col.colors[0]) * p1->h);

				put_pixel((int)p1->x, y, col.ARGB, data);
			}
		}
		p1->col.colors[2] += cb_r;
		p1->col.colors[1] += cb_g;
		p1->col.colors[0] += cb_b;
		p1->h += a;
		p1->x++;
		p1->z += ZB;
	}
}

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

	draw_horizontal_line(&p1, &p2, y, data);
}