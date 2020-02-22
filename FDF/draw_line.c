/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 16:43:28 by mcamila           #+#    #+#             */
/*   Updated: 2020/02/22 03:46:26 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

inline void		swap_f(float *a, float *b)
{
	float temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

inline void		swap_2pt(t_pt2 *a, t_pt2 *b)
{
	t_pt2 temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

inline void		swap_colors(t_color *a, t_color *b)
{
	t_color temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

inline float	absolute(float x)
{
	if (x < 0)
		return (-x);
	else
		return (x);
}

void	initializate_ln(t_hln *ln, t_draw *s)
{
	ln->x = (s->X1);
	ln->h = (s->H1);
	ln->a = ((s->H2) - (s->H1)) / ((s->X2) - (s->X1));
	ln->z0 = (s->ZB1);
	ln->zb = ((s->ZB2 - (s->ZB1)) / ((s->X2) - (s->X1)));
	ln->col.ARGB = 0;
	ln->c_r = s->col1.colors[2];
	ln->c_g = s->col1.colors[1];
	ln->c_b = s->col1.colors[0];
	ln->cb_r = (float)(s->col2.colors[2] - s->col1.colors[2])
			/ ((s->X2) - (s->X1));
	ln->cb_g = (float)(s->col2.colors[1] - s->col1.colors[1])
			/ ((s->X2) - (s->X1));
	ln->cb_b = (float)(s->col2.colors[0] - s->col1.colors[0])
			/ ((s->X2) - (s->X1));
}

void	draw_pixel(int y, t_data *data, t_hln *ln)
{
	data->zbuff[((int)ln->x + (y * (WIDTH))) - 1] = ln->z0;
	ln->col.colors[2] = (char)(ln->c_r * data->disco);
	ln->col.colors[1] = (char)(ln->c_g * data->disco);
	ln->col.colors[0] = (char)(ln->c_b * data->disco);
	ln->col.colors[2] = (char)(ln->col.colors[2] * ln->h);
	ln->col.colors[1] = (char)(ln->col.colors[1] * ln->h);
	ln->col.colors[0] = (char)(ln->col.colors[0] * ln->h);
	put_pixel((int)ln->x, y, ln->col.ARGB, data);
}

void	draw_hor_line(t_draw s, int y, t_data *data)
{
	t_hln	ln;

	if ((s.X1) == (s.X2))
		return ;
	if ((s.X1) > (s.X2))
	{
		swap_f(&(s.X1), &(s.X2));
		swap_f(&(s.H1), &(s.H2));
		swap_f(&(s.ZB1), &(s.ZB2));
		swap_colors(&s.col1, &s.col2);
	}
	initializate_ln(&ln, &s);
	while (ln.x <= (s.X2))
	{
		if ((ln.x >= 0 && (int)ln.x < WIDTH) && (y >= 0 && y < HIEGHT)
		&& (ln.z0 >= data->zbuff[((int)ln.x + (y * WIDTH)) - 1]))
			draw_pixel(y, data, &ln);
		ln.c_r += ln.cb_r;
		ln.c_g += ln.cb_g;
		ln.c_b += ln.cb_b;
		ln.h += ln.a;
		ln.x++;
		ln.z0 += ln.zb;
	}
}

inline void	initializate_a(t_pt2 p0, t_pt2 p1, t_pt2 p2, t_draw *s)
{
	s->a1 = absolute(p0.x - p1.x) / (p1.y - p0.y);
	s->a2 = absolute(p0.x - p2.x) / (p2.y - p0.y);
	if (p0.x > p1.x)
		s->a1 = -s->a1;
	if (p0.x > p2.x)
		s->a2 = -s->a2;
}

inline void	initializate_s_1(t_pt2 p0, t_pt2 p1, t_pt2 p2, t_draw *s)
{
	initializate_a(p0, p1, p2, s);
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
	s->C_R1 = p0.c.colors[2];
	s->C_G1 = p0.c.colors[1];
	s->C_B1 = p0.c.colors[0];
	s->C_R2 = p0.c.colors[2];
	s->C_G2 = p0.c.colors[1];
	s->C_B2 = p0.c.colors[0];
	s->cb_r1 = (float)(p1.c.colors[2] - p0.c.colors[2]) / (p1.y - p0.y);
	s->cb_g1 = (float)(p1.c.colors[1] - p0.c.colors[1]) / (p1.y - p0.y);
	s->cb_b1 = (float)(p1.c.colors[0] - p0.c.colors[0]) / (p1.y - p0.y);
	s->cb_r2 = (float)(p2.c.colors[2] - p0.c.colors[2]) / (p2.y - p0.y);
	s->cb_g2 = (float)(p2.c.colors[1] - p0.c.colors[1]) / (p2.y - p0.y);
	s->cb_b2 = (float)(p2.c.colors[0] - p0.c.colors[0]) / (p2.y - p0.y);
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
	s->C_R1 = p1.c.colors[2];
	s->C_G1 = p1.c.colors[1];
	s->C_B1 = p1.c.colors[0];
	s->cb_r1 = (float)(p2.c.colors[2] - p1.c.colors[2]) / (p2.y - p1.y);
	s->cb_g1 = (float)(p2.c.colors[1] - p1.c.colors[1]) / (p2.y - p1.y);
	s->cb_b1 = (float)(p2.c.colors[0] - p1.c.colors[0]) / (p2.y - p1.y);
}

inline void	draw_tri_1(t_draw *s, t_data *data, int y)
{
	s->col1.colors[2] = (char)s->C_R1;
	s->col1.colors[1] = (char)s->C_G1;
	s->col1.colors[0] = (char)s->C_B1;
	s->col2.colors[2] = (char)s->C_R2;
	s->col2.colors[1] = (char)s->C_G2;
	s->col2.colors[0] = (char)s->C_B2;
	draw_hor_line(*s, (int)y, data);
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

inline void	draw_tri_2(t_draw *s, t_data *data, int y)
{
	s->col1.colors[2] = (char)s->C_R1;
	s->col2.colors[2] = (char)s->C_R2;
	s->col1.colors[1] = (char)s->C_G1;
	s->col2.colors[1] = (char)s->C_G2;
	s->col1.colors[0] = (char)s->C_B1;
	s->col2.colors[0] = (char)s->C_B2;
	draw_hor_line(*s, (int)y, data);
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

void	draw_tri(t_pt2 p0, t_pt2 p1, t_pt2 p2, t_data *data)
{
	t_draw	s;
	float	y;

	if (p0.y > p1.y)
		swap_2pt(&p1, &p0);
	if (p0.y > p2.y)
		swap_2pt(&p2, &p0);
	if (p1.y > p2.y)
		swap_2pt(&p2, &p1);
	initializate_s_1(p0, p1, p2, &s);
	y = p0.y - 1;
	s.col1.ARGB = 0;
	s.col2.ARGB = 0;
	while (++y < (float)((int)p1.y))
		draw_tri_1(&s, data, y);
	initializate_s_2(p0, p1, p2, &s);
	while (y <= (float)((int)p2.y))
	{
		draw_tri_2(&s, data, y);
		y++;
	}
}
