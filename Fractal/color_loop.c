/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 04:44:58 by mcamila           #+#    #+#             */
/*   Updated: 2020/02/26 02:00:09 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

inline int	color_add_6(t_color *c)
{
	c->colors[0]--;
	c->colors[1]++;
	return (1);
}

inline int	color_add_11(t_color *c)
{
	if (c->colors[2] == 0 && color_add_1(c))
		return (1);
	if (c->colors[0] != 255 && color_add_2(c))
		return (1);
	return (1);
}

inline int	color_add_22(t_color *c)
{
	if (c->colors[1] == 0 && color_add_3(c))
		return (1);
	if (c->colors[2] != 255 && color_add_4(c))
		return (1);
	c->colors[1]--;
	return (1);
}

inline int	color_add_33(t_color *c)
{
	if (c->colors[0] == 0 && color_add_5(c))
		return (1);
	if (c->colors[1] != 255 && color_add_6(c))
		return (1);
	c->colors[0]--;
	return (1);
}

t_color		color_loop(unsigned int speed, t_color c)
{
	int				j;

	j = -1;
	while (++j < (int)speed)
	{
		if (c.colors[1] == 255 && color_add_11(&c))
			continue;
		if (c.colors[0] == 255 && color_add_22(&c))
			continue;
		if (c.colors[2] == 255 && color_add_33(&c))
			continue;
		c.colors[0]++;
	}
	return (c);
}
