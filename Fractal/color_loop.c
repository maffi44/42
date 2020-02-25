/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 04:44:58 by mcamila           #+#    #+#             */
/*   Updated: 2020/02/24 19:27:52 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

inline int	color_add_6(t_color *c, t_ref_obj *obj, int i)
{
	c->colors[0]--;
	c->colors[1]++;
	obj->vertex[i].color = c->argb;
	return (1);
}

inline int	color_add_11(t_color *c, t_ref_obj *obj, int i)
{
	if (c->colors[2] == 0 && color_add_1(c, obj, i))
		return (1);
	if (c->colors[0] != 255 && color_add_2(c, obj, i))
		return (1);
	c->colors[2]--;
	obj->vertex[i].color = c->argb;
	return (1);
}

inline int	color_add_22(t_color *c, t_ref_obj *obj, int i)
{
	if (c->colors[1] == 0 && color_add_3(c, obj, i))
		return (1);
	if (c->colors[2] != 255 && color_add_4(c, obj, i))
		return (1);
	c->colors[1]--;
	obj->vertex[i].color = c->argb;
	return (1);
}

inline int	color_add_33(t_color *c, t_ref_obj *obj, int i)
{
	if (c->colors[0] == 0 && color_add_5(c, obj, i))
		return (1);
	if (c->colors[1] != 255 && color_add_6(c, obj, i))
		return (1);
	c->colors[0]--;
	obj->vertex[i].color = c->argb;
	return (1);
}

inline void	color_loop(t_ref_obj *obj, unsigned int speed)
{
	t_color			c;
	int				i;
	int				j;

	i = -1;
	while (++i - 1 < obj->num_of_pts - 1)
	{
		c.argb = obj->vertex[i].color;
		j = -1;
		while (++j < (int)speed)
		{
			if (c.colors[1] == 255 && color_add_11(&c, obj, i))
				continue;
			if (c.colors[0] == 255 && color_add_22(&c, obj, i))
				continue;
			if (c.colors[2] == 255 && color_add_33(&c, obj, i))
				continue;
			c.colors[0]++;
			obj->vertex[i].color = c.argb;
		}
	}
}
