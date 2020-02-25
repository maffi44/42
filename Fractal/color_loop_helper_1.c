/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_loop_helper_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 04:42:49 by mcamila           #+#    #+#             */
/*   Updated: 2020/02/24 19:27:52 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

inline int	color_add_1(t_color *c, t_ref_obj *obj, int i)
{
	c->colors[1]--;
	c->colors[2]++;
	obj->vertex[i].color = c->argb;
	return (1);
}

inline int	color_add_2(t_color *c, t_ref_obj *obj, int i)
{
	c->colors[2]--;
	c->colors[0]++;
	obj->vertex[i].color = c->argb;
	return (1);
}

inline int	color_add_3(t_color *c, t_ref_obj *obj, int i)
{
	c->colors[0]--;
	c->colors[1]++;
	obj->vertex[i].color = c->argb;
	return (1);
}

inline int	color_add_4(t_color *c, t_ref_obj *obj, int i)
{
	c->colors[1]--;
	c->colors[2]++;
	obj->vertex[i].color = c->argb;
	return (1);
}

inline int	color_add_5(t_color *c, t_ref_obj *obj, int i)
{
	c->colors[2]--;
	c->colors[0]++;
	obj->vertex[i].color = c->argb;
	return (1);
}
