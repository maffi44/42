/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 16:43:28 by mcamila           #+#    #+#             */
/*   Updated: 2020/02/24 19:28:54 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

inline void		initializate_s_1(t_pt2 p0, t_pt2 p1, t_pt2 p2, t_draw *s)
{
	initializate_a(p0, p1, p2, s);
	s->x1 = p0.x;
	s->x2 = p0.x;
	s->h1 = p0.light;
	s->h2 = p0.light;
	s->b1 = (p1.light - p0.light) / (p1.y - p0.y);
	s->b2 = (p2.light - p0.light) / (p2.y - p0.y);
	s->z1 = p0.z1;
	s->z2 = p0.z1;
	s->zb1 = (p1.z1 - p0.z1) / (p1.y - p0.y);
	s->zb2 = (p2.z1 - p0.z1) / (p2.y - p0.y);
	s->c_r1 = p0.c.colors[2];
	s->c_g1 = p0.c.colors[1];
	s->c_b1 = p0.c.colors[0];
	s->c_r2 = p0.c.colors[2];
	s->c_g2 = p0.c.colors[1];
	s->c_b2 = p0.c.colors[0];
	s->cb_r1 = (float)(p1.c.colors[2] - p0.c.colors[2]) / (p1.y - p0.y);
	s->cb_g1 = (float)(p1.c.colors[1] - p0.c.colors[1]) / (p1.y - p0.y);
	s->cb_b1 = (float)(p1.c.colors[0] - p0.c.colors[0]) / (p1.y - p0.y);
	s->cb_r2 = (float)(p2.c.colors[2] - p0.c.colors[2]) / (p2.y - p0.y);
	s->cb_g2 = (float)(p2.c.colors[1] - p0.c.colors[1]) / (p2.y - p0.y);
	s->cb_b2 = (float)(p2.c.colors[0] - p0.c.colors[0]) / (p2.y - p0.y);
}

inline void		initializate_s_2(t_pt2 p1, t_pt2 p2, t_draw *s)
{
	s->x1 = p1.x;
	s->a1 = absolute(p1.x - p2.x) / (p2.y - p1.y);
	if (p1.x > p2.x)
		s->a1 = -s->a1;
	s->h1 = p1.light;
	s->b1 = (p1.light - p2.light) / (p1.y - p2.y);
	s->zb1 = p1.z1;
	s->zb1 = (p2.z1 - p1.z1) / (p2.y - p1.y);
	s->c_r1 = p1.c.colors[2];
	s->c_g1 = p1.c.colors[1];
	s->c_b1 = p1.c.colors[0];
	s->cb_r1 = (float)(p2.c.colors[2] - p1.c.colors[2]) / (p2.y - p1.y);
	s->cb_g1 = (float)(p2.c.colors[1] - p1.c.colors[1]) / (p2.y - p1.y);
	s->cb_b1 = (float)(p2.c.colors[0] - p1.c.colors[0]) / (p2.y - p1.y);
}

inline void		draw_tri_1(t_draw *s, t_data *data, int y)
{
	s->col1.colors[2] = (char)s->c_r1;
	s->col1.colors[1] = (char)s->c_g1;
	s->col1.colors[0] = (char)s->c_b1;
	s->col2.colors[2] = (char)s->c_r2;
	s->col2.colors[1] = (char)s->c_g2;
	s->col2.colors[0] = (char)s->c_b2;
	draw_hor_line(*s, (int)y, data);
	s->x1 += s->a1;
	s->x2 += s->a2;
	s->h1 += s->b1;
	s->h2 += s->b2;
	s->z1 += s->zb1;
	s->z2 += s->zb2;
	s->c_r1 += s->cb_r1;
	s->c_r2 += s->cb_r2;
	s->c_g1 += s->cb_g1;
	s->c_g2 += s->cb_g2;
	s->c_b1 += s->cb_b1;
	s->c_b2 += s->cb_b2;
}

inline void		draw_tri_2(t_draw *s, t_data *data, int y)
{
	s->col1.colors[2] = (char)s->c_r1;
	s->col2.colors[2] = (char)s->c_r2;
	s->col1.colors[1] = (char)s->c_g1;
	s->col2.colors[1] = (char)s->c_g2;
	s->col1.colors[0] = (char)s->c_b1;
	s->col2.colors[0] = (char)s->c_b2;
	draw_hor_line(*s, (int)y, data);
	s->x1 += s->a1;
	s->x2 += s->a2;
	s->h1 += s->b1;
	s->h2 += s->b2;
	s->z1 += s->zb1;
	s->z2 += s->zb2;
	s->c_r1 += s->cb_r1;
	s->c_r2 += s->cb_r2;
	s->c_g1 += s->cb_g1;
	s->c_g2 += s->cb_g2;
	s->c_b1 += s->cb_b1;
	s->c_b2 += s->cb_b2;
}

void			draw_tri(t_pt2 p0, t_pt2 p1, t_pt2 p2, t_data *data)
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
	s.col1.argb = 0;
	s.col2.argb = 0;
	while (++y < (float)((int)(p1.y)))
		draw_tri_1(&s, data, y);
	initializate_s_2(p1, p2, &s);
	while (y <= (float)((int)p2.y))
	{
		draw_tri_2(&s, data, y);
		y++;
	}
}
