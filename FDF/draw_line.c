/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 16:43:28 by mcamila           #+#    #+#             */
/*   Updated: 2020/02/21 12:20:46 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

inline void swap_f(float *a, float *b)
{
	float temp = *a;
	*a = *b;
	*b = temp;
}

inline void swap_2pt(t_pt2 *a, t_pt2 *b)
{
	t_pt2 temp = *a;
	*a = *b;
	*b = temp;
}

inline void swap_colors(t_color *a, t_color *b)
{
	t_color temp = *a;
	*a = *b;
	*b = temp;
}

inline void swap(int* a , int*b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

inline float absolute(float x )
{
	if (x < 0) return -x;
	else return x;
}

void	draw_line (int x0, int y0, int x1, int y1, t_data *data, int color)
{
	int dx;
	int dy;
	if (x0 == x1 && y0 == y1)
	{
		put_pixel(x0, y0, color, data);
		return;
	}
	if (absolute(x0 - x1) > absolute(y0 - y1)) {
		if (x0 > x1) {
			swap(&x0, &x1);
			swap(&y0, &y1);
		}
		dx = x0 - x1;
		dy = y0 - y1;
		double a;
		a = (double) dy / (double) dx;
		double x;
		double y;
		x = x0;
		y = y0;
		while (x <= x1) {
			put_pixel((int) x, (int) y, color, data);
			y += a;
			x++;
		}
	} else
	{
		if (y0 > y1) {
			swap(&x0, &x1);
			swap(&y0, &y1);
		}
		dx = x0 - x1;
		dy = y0 - y1;
		double a;
		a = (double) dx / (double) dy;
		double x;
		double y;
		x = x0;
		y = y0;
		while (y <= y1) {
			put_pixel((int) x, (int) y, color, data);
			x += a;
			y++;
		}
	}
}

void draw_hor_line(float x0, float x1, int y, t_data *data, float h0, float h1, float zb1, float zb2, t_color col0, t_color col1)
{
	if (x0 == x1)
		return;

	if (x0 > x1)
	{
		swap_f(&x0, &x1);
		swap_f(&h0, &h1);
		swap_f(&zb1, &zb2);
		swap_colors(&col0, &col1);
	}
	double h = h0;
	float a = (h1 - h0) / (x1 - x0);

	float Z0 = zb1;
	float ZB =	(zb2 - zb1) / (x1 - x0);

	t_color col;
	col.ARGB = 0;

	float C_R = col0.colors[2];
	float C_G = col0.colors[1];
	float C_B = col0.colors[0];
	float cb_r = (float)(col1.colors[2] - col0.colors[2]) / (x1 - x0);
	float cb_g = (float)(col1.colors[1] - col0.colors[1]) / (x1 - x0);
	float cb_b = (float)(col1.colors[0] - col0.colors[0]) / (x1 - x0);

	while (x0 <= x1)
	{
		if ((x0 >= 0 && (int)x0 < WIDTH) && (y >= 0 && y < HIEGHT))
		{
			if (Z0 >= data->zbuff[((int)x0 + (y * WIDTH)) - 1])
			{
				data->zbuff[((int)x0 + (y * (WIDTH))) - 1] = Z0;
				col.colors[2] = (char) (C_R * data->disco);
				col.colors[1] = (char) (C_G * data->disco);
				col.colors[0] = (char) (C_B * data->disco);
//				col.colors[2] *= h;
//				col.colors[1] *= h;
//				col.colors[0] *= h;
				col.colors[2] = (char)(col.colors[2] * h);
				col.colors[1] = (char)(col.colors[1] * h);
				col.colors[0] = (char)(col.colors[0] * h);
//				col.colors[2] = (char) (C_R * h);
//				col.colors[1] = (char) (C_G * h);
//				col.colors[0] = (char) (C_B * h);
				put_pixel((int)x0, y, col.ARGB, data);
			}
		}
		C_R += cb_r;
		C_G += cb_g;
		C_B += cb_b;
		h += a;
		x0++;
		Z0 += ZB;
	}
}

typedef struct	s_draw
{
	float a1;
	float a2;
	float X1;
	float X2;
	float H1;
	float H2;
	float b1;
	float b2;
	float ZB1;
	float ZB2;
	float zb1;
	float zb2;
	float C_R1;
	float C_G1;
	float C_B1;
	float C_R2;
	float C_G2;
	float C_B2;
	float cb_r1;
	float cb_g1;
	float cb_b1;
	float cb_r2;
	float cb_g2;
	float cb_b2;
}				t_draw;

void	initializate_s_1(t_pt2 p0, t_pt2 p1, t_pt2 p2, t_draw *s);
void	initializate_s_2(t_pt2 p0, t_pt2 p1, t_pt2 p2, t_draw *s);

inline void	initializate_s_1(t_pt2 p0, t_pt2 p1, t_pt2 p2, t_draw *s)
{
	s->a1 = absolute(p0.x - p1.x) / (p1.y - p0.y);
	s->a2 = absolute(p0.x - p2.x) / (p2.y - p0.y);
	if (p0.x > p1.x)
		s->a1 = -s->a1;
	if (p0.x > p2.x)
		s->a2 = -s->a2;
	s->X1 = p0.x;
	s->X2 = p0.x;
	s->H1 = p0.light;
	s->H2 = p0.light;
	s->b1 = (p1.light - p0.light) / (p1.y - p0.y);
	s->b2 = (p2.light - p0.light) / (p2.y - p0.y);
	s->ZB1 = p0.z1;
	s->ZB2 = p0.z1;
	s->zb1 = (p1.z1 - p0.z1) / (p1.y - p0.y);
	s->zb2 = (p2.z1 - p0.z1) / (p2.y - p0.y);
	s->C_R1 = p0.color.colors[2];
	s->C_G1 = p0.color.colors[1];
	s->C_B1 = p0.color.colors[0];
	s->C_R2 = p0.color.colors[2];
	s->C_G2 = p0.color.colors[1];
	s->C_B2 = p0.color.colors[0];
	s->cb_r1 = (float)(p1.color.colors[2] - p0.color.colors[2]) / (p1.y - p0.y);
	s->cb_g1 = (float)(p1.color.colors[1] - p0.color.colors[1]) / (p1.y - p0.y);
	s->cb_b1 = (float)(p1.color.colors[0] - p0.color.colors[0]) / (p1.y - p0.y);
	s->cb_r2 = (float)(p2.color.colors[2] - p0.color.colors[2]) / (p2.y - p0.y);
	s->cb_g2 = (float)(p2.color.colors[1] - p0.color.colors[1]) / (p2.y - p0.y);
	s->cb_b2 = (float)(p2.color.colors[0] - p0.color.colors[0]) / (p2.y - p0.y);
}

inline void	initializate_s_2(t_pt2 p0, t_pt2 p1, t_pt2 p2, t_draw *s)
{
	s->X1 = p1.x;
	s->a1 = absolute(p1.x - p2.x) / (p2.y - p1.y);
	if (p1.x > p2.x)
		s->a1 = -s->a1;
	s->H1 = p1.light;
	s->b1 = (p1.light - p2.light) / (p1.y - p2.y);
	s->ZB1 = p1.z1;
	s->zb1 = (p2.z1 - p1.z1) / (p2.y - p1.y);
	s->C_R1 = p1.color.colors[2];
	s->C_G1 = p1.color.colors[1];
	s->C_B1 = p1.color.colors[0];
	s->cb_r1 = (float)(p2.color.colors[2] - p1.color.colors[2]) / (p2.y - p1.y);
	s->cb_g1 = (float)(p2.color.colors[1] - p1.color.colors[1]) / (p2.y - p1.y);
	s->cb_b1 = (float)(p2.color.colors[0] - p1.color.colors[0]) / (p2.y - p1.y);
}

inline void	draw_tri_1(t_draw *s, t_data *data, t_color col1, t_color col2, int y)
{
	col1.colors[2] = (char)s->C_R1;
	col1.colors[1] = (char)s->C_G1;
	col1.colors[0] = (char)s->C_B1;
	col2.colors[2] = (char)s->C_R2;
	col2.colors[1] = (char)s->C_G2;
	col2.colors[0] = (char)s->C_B2;
	draw_hor_line(s->X1, s->X2, (int)y, data, s->H1, s->H2, s->ZB1, s->ZB2, col1, col2);
	s->X1 += s->a1;
	s->X2 += s->a2;
	s->H1 += s->b1;
	s->H2 += s->b2;
	s->ZB1 += s->zb1;
	s->ZB2 += s->zb2;
	s->C_R1 += s->cb_r1;
	s->C_R2 += s->cb_r2;
	s->C_G1 += s->cb_g1;
	s->C_G2 += s->cb_g2;
	s->C_B1 += s->cb_b1;
	s->C_B2 += s->cb_b2;
}

inline void	draw_tri_2(t_draw *s, t_data *data, t_color col1, t_color col2, int y)
{
	col1.colors[2] = (char)s->C_R1;
	col2.colors[2] = (char)s->C_R2;
	col1.colors[1] = (char)s->C_G1;
	col2.colors[1] = (char)s->C_G2;
	col1.colors[0] = (char)s->C_B1;
	col2.colors[0] = (char)s->C_B2;
	draw_hor_line(s->X1, s->X2, (int)y, data, s->H1, s->H2, s->ZB1, s->ZB2, col1, col2);
	s->X1 += s->a1;
	s->X2 += s->a2;
	s->H1 += s->b1;
	s->H2 += s->b2;
	s->ZB1 += s->zb1;
	s->ZB2 += s->zb2;
	s->C_R1 += s->cb_r1;
	s->C_R2 += s->cb_r2;
	s->C_G1 += s->cb_g1;
	s->C_G2 += s->cb_g2;
	s->C_B1 += s->cb_b1;
	s->C_B2 += s->cb_b2;
}

void draw_tri(t_pt2 p0, t_pt2 p1, t_pt2 p2, t_data *data) {
	t_draw s;
	float y;
	t_color col1;
	t_color col2;

	if (p0.y > p1.y)
		swap_2pt(&p1, &p0);
	if (p0.y > p2.y)
		swap_2pt(&p2, &p0);
	if (p1.y > p2.y)
		swap_2pt(&p2, &p1);
	initializate_s_1(p0, p1, p2, &s);
	y = p0.y;
	col1.ARGB = 0;
	col2.ARGB = 0;
	while (y < (int)p1.y)
	{
		draw_tri_1(&s, data, col1, col2, y);
		y++;
	}
	initializate_s_2(p0, p1, p2, &s);
	while (y <= (int)p2.y)
	{
		draw_tri_2(&s, data, col1, col2, y);
		y++;
	}
}
