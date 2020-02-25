/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_tri_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 04:34:27 by mcamila           #+#    #+#             */
/*   Updated: 2020/02/24 19:27:52 by mcamila          ###   ########.fr       */
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

inline void		initializate_a(t_pt2 p0, t_pt2 p1, t_pt2 p2, t_draw *s)
{
	s->a1 = absolute(p0.x - p1.x) / (p1.y - p0.y);
	s->a2 = absolute(p0.x - p2.x) / (p2.y - p0.y);
	if (p0.x > p1.x)
		s->a1 = -s->a1;
	if (p0.x > p2.x)
		s->a2 = -s->a2;
}
