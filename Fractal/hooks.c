/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 05:22:04 by mcamila           #+#    #+#             */
/*   Updated: 2020/02/26 07:38:34 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		key_press(int key, t_data *data)
{
	if (key == 53)
		go_away(data);
	if (key == 27)
	{
		data->p.sc *= 1.12f;
		if (data->p.sc > 1.f)
			data->p.sc = 1.f;
	}
	if (key == 24)
	{
		data->p.sc *= 0.88f;
	}
	if (key == 33)
	{
		if (data->p.max_iteration > 10)
			data->p.max_iteration -= 10;
	}
	if (key == 30)
	{
		data->p.max_iteration += 10;
	}
	ft_render(data);
	return (0);
}

int		key_release(int key, t_data *data)
{
	if (key == 3)
	{
		if (data->p.fract < 6)
			data->p.fract++;
		else
			data->p.fract = 0;
	}
	ft_render(data);
	return (0);
}

int		mouse_press(int button, int x, int y, t_data *data)
{
	if (button == 1)
		data->p.jul_bool = !data->p.jul_bool;
	if (button == 4)
		data->p.sc *= 0.95f;
	if (button == 5)
	{
		data->p.sc *= 1.05f;
		if (data->p.sc > 1.f)
			data->p.sc = 1.f;
	}
	if (button == 3)
	{
		data->p.x = x;
		data->p.y = y;
		data->p.m_bool = 1;
	}
	ft_render(data);
	return (0);
}

int		x_press(void *data)
{
	go_away(data);
	return (0);
}
