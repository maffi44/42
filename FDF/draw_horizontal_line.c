/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_horizontal_line.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 01:14:36 by mcamila           #+#    #+#             */
/*   Updated: 2020/02/22 04:40:24 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

inline void		initializate_ln(t_hln *ln, t_draw *s)
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

inline void		draw_pixel(int y, t_data *data, t_hln *ln)
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

void			draw_hor_line(t_draw s, int y, t_data *data)
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
