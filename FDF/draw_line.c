/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 16:43:28 by mcamila           #+#    #+#             */
/*   Updated: 2020/02/20 20:50:31 by mcamila          ###   ########.fr       */
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
				if (data->disco)
					h = data->disco + 1;
				data->zbuff[((int)x0 + (y * (WIDTH))) - 1] = Z0;
				col.colors[2] = (char) (C_R * h);
				col.colors[1] = (char) (C_G * h);
				col.colors[0] = (char) (C_B * h);
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

void draw_tri(t_pt2 p0, t_pt2 p1, t_pt2 p2, t_data *data) {
	if (p0.y > p1.y)
		swap_2pt(&p1, &p0);
	if (p0.y > p2.y)
		swap_2pt(&p2, &p0);
	if (p1.y > p2.y)
		swap_2pt(&p2, &p1);
	float y = p0.y;
	float a1 = absolute(p0.x - p1.x) / (p1.y - p0.y);
	float a2 = absolute(p0.x - p2.x) / (p2.y - p0.y);
	if (p0.x > p1.x)
		a1 = -a1;
	if (p0.x > p2.x)
		a2 = -a2;
	float X1 = p0.x;
	float X2 = p0.x;
	float H1 = p0.light;
	float H2 = p0.light;
	float b1 = (p1.light - p0.light) / (p1.y - p0.y);
	float b2 = (p2.light - p0.light) / (p2.y - p0.y);
	float ZB1 = p0.z1;
	float ZB2 = p0.z1;
	float zb1 = (p1.z1 - p0.z1) / (p1.y - p0.y);
	float zb2 = (p2.z1 - p0.z1) / (p2.y - p0.y);
	float C_R1 = p0.color.colors[2];
	float C_G1 = p0.color.colors[1];
	float C_B1 = p0.color.colors[0];
	float C_R2 = p0.color.colors[2];
	float C_G2 = p0.color.colors[1];
	float C_B2 = p0.color.colors[0];
	float cb_r1 = (float)(p1.color.colors[2] - p0.color.colors[2]) / (p1.y - p0.y);
	float cb_g1 = (float)(p1.color.colors[1] - p0.color.colors[1]) / (p1.y - p0.y);
	float cb_b1 = (float)(p1.color.colors[0] - p0.color.colors[0]) / (p1.y - p0.y);
	float cb_r2 = (float)(p2.color.colors[2] - p0.color.colors[2]) / (p2.y - p0.y);
	float cb_g2 = (float)(p2.color.colors[1] - p0.color.colors[1]) / (p2.y - p0.y);
	float cb_b2 = (float)(p2.color.colors[0] - p0.color.colors[0]) / (p2.y - p0.y);
	t_color col1;
	t_color col2;
	col1.ARGB = 0;
	col2.ARGB = 0;
	while (y < (int)p1.y)
	{
		col1.colors[2] = (char)C_R1;
		col1.colors[1] = (char)C_G1;
		col1.colors[0] = (char)C_B1;
		col2.colors[2] = (char)C_R2;
		col2.colors[1] = (char)C_G2;
		col2.colors[0] = (char)C_B2;
		draw_hor_line(X1, X2, (int)y, data, H1, H2, ZB1, ZB2, col1, col2);
		X1 += a1;
		X2 += a2;
		H1 += b1;
		H2 += b2;
		ZB1 += zb1;
		ZB2 += zb2;
		C_R1 += cb_r1;
		C_R2 += cb_r2;
		C_G1 += cb_g1;
		C_G2 += cb_g2;
		C_B1 += cb_b1;
		C_B2 += cb_b2;
		y++;
	}
	X1 = p1.x;
	a1 = absolute(p1.x - p2.x) / (p2.y - p1.y);
	if (p1.x > p2.x)
		a1 = -a1;
	H1 = p1.light;
	b1 = (p1.light - p2.light) / (p1.y - p2.y);
	ZB1 = p1.z1;
	zb1 = (p2.z1 - p1.z1) / (p2.y - p1.y);
	C_R1 = p1.color.colors[2];
	C_G1 = p1.color.colors[1];
	C_B1 = p1.color.colors[0];
	cb_r1 = (float)(p2.color.colors[2] - p1.color.colors[2]) / (p2.y - p1.y);
	cb_g1 = (float)(p2.color.colors[1] - p1.color.colors[1]) / (p2.y - p1.y);
	cb_b1 = (float)(p2.color.colors[0] - p1.color.colors[0]) / (p2.y - p1.y);
	while (y <= (int)p2.y)
	{
		col1.colors[2] = (char)C_R1;
		col2.colors[2] = (char)C_R2;
		col1.colors[1] = (char)C_G1;
		col2.colors[1] = (char)C_G2;
		col1.colors[0] = (char)C_B1;
		col2.colors[0] = (char)C_B2;
		draw_hor_line(X1, X2, (int)y, data, H1, H2, ZB1, ZB2, col1, col2);
		X1 += a1;
		X2 += a2;
		H1 += b1;
		H2 += b2;
		ZB1 += zb1;
		ZB2 += zb2;
		C_R1 += cb_r1;
		C_R2 += cb_r2;
		C_G1 += cb_g1;
		C_G2 += cb_g2;
		C_B1 += cb_b1;
		C_B2 += cb_b2;
		y++;
	}
}
