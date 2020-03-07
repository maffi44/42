/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 05:22:04 by mcamila           #+#    #+#             */
/*   Updated: 2020/02/22 05:23:23 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		key_press(int key, t_data *data)
{
	if (key == 53)
		go_away(data);
	else if (key == 15)
		data->r_bool = 1;
	else if (key == 12)
		data->q_bool = !(data->q_bool);
	else if (key == 4)
		data->h_bool = 1;
	else if (key == 3)
		data->f_bool = 1;
	else if (key == 24)
		data->disco++;
	else if (key == 27)
		if (data->disco > 1)
			data->disco--;
	return (0);
}

int		key_release(int key, t_data *data)
{
	if (key == 15)
		data->r_bool = 0;
	else if (key == 4)
		data->h_bool = 0;
	else if (key == 3)
		data->f_bool = 0;
	return (0);
}

void	mouse_scale_p(t_data *data)
{
	if (data->h_bool)
	{
		data->obj_inst->scale.elem[1][1] *= 0.95f;
	}
	else if (data->f_bool)
	{
		if ((data->d += 0.05f) > 4)
			data->d = 4;
	}
	else
	{
		data->obj_inst->scale.elem[0][0] *= 0.95f;
		data->obj_inst->scale.elem[1][1] *= 0.95f;
		data->obj_inst->scale.elem[2][2] *= 0.95f;
	}
}

void	mouse_scale_m(t_data *data)
{
	if (data->h_bool)
	{
		data->obj_inst->scale.elem[1][1] *= 1.05f;
	}
	else if (data->f_bool)
	{
		if ((data->d -= 0.05f) < 0.1f)
			data->d = 0.1f;
	}
	else
	{
		data->obj_inst->scale.elem[0][0] *= 1.05f;
		data->obj_inst->scale.elem[1][1] *= 1.05f;
		data->obj_inst->scale.elem[2][2] *= 1.05f;
	}
}

int		mouse_press(int button, int x, int y, t_data *data)
{
	if (button == 1)
	{
		((t_data *)data)->mouse_bool = 1;
		((t_data *)data)->x = x;
		((t_data *)data)->y = y;
	}
	if (button == 4)
	{
		mouse_scale_m(data);
		render_frame(data->obj_inst, 1, data);
	}
	if (button == 5)
	{
		mouse_scale_p(data);
		render_frame(data->obj_inst, 1, data);
	}
	return (0);
}
