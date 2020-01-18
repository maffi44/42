/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 16:21:28 by mcamila           #+#    #+#             */
/*   Updated: 2020/01/18 19:17:24 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	go_away(t_data *data)
{
	if (data)
	{
		if (data->mlx_ptr)
			free(data->mlx_ptr);
		if (data->win_ptr)
			free(data->win_ptr);
		free(data);
		data = NULL;
	}
	exit(0);
}

int expose(void *data)
{
//	if (((t_data*)data)->mouse_bool)
//		mlx_pixel_put(((t_data*)data)->mlx_ptr, ((t_data*)data)->win_ptr, ((t_data*)data)->x, ((t_data*)data)->y, 0x00FFFFFF);
	return (0);
}

int	key_press(int key, void *data)
{
	if (key == 53)
		go_away(data);
	return (0);
}

int	key_release(int key, void *param)
{
	return (0);
}

int mouse_press(int button, int x, int y, void *data)
{
	if (button == 1)
	{
		if (((t_data *) data)->mouse_bool == 0) {
			((t_data *) data)->mouse_bool = 1;
			((t_data *) data)->x = x;
			((t_data *) data)->y = y;
		}
		else
		{
			//((t_data *) data)->mouse_bool = 0;
			draw_line(((t_data *) data)->x, ((t_data *) data)->y, x, y, data);
			((t_data *) data)->x = x;
			((t_data *) data)->y = y;
		}
	}
	return (0);
}

int	mouse_release(int button, int x, int y, void *data)
{
//	if (button == 1)
//		((t_data *) data)->mouse_bool = 0;
	return (0);
}

int	mouse_move(int x, int y, t_data *data)
{
//	if (((t_data*)data)->mouse_bool)
//	{
//		draw_line(x, y, ((t_data*)data)->x, ((t_data*)data)->y, data);
//		((t_data*)data)->x = x;
//		((t_data*)data)->y = y;
//	}
	return (0);
}

int	x_press(void *data)
{
	go_away(data);
	return (0);
}

int	main() {
	t_data	*data;

	if (!(data = (t_data*)malloc(sizeof(t_data))))
		go_away(data);
	if (!(data->mlx_ptr = mlx_init()))
		go_away(data);
	if (!(data->win_ptr = mlx_new_window(data->mlx_ptr, 1920, 1080, "rissovalka")))
		go_away(data);
	data->mouse_bool = 0;

	draw_line(0, 0, 100, 500, data);

	mlx_hook(data->win_ptr, 2, 0, key_press, data);
	mlx_hook(data->win_ptr, 3, 0, key_release, (void*)0);
	mlx_hook(data->win_ptr, 4, 0, mouse_press, data);
	mlx_hook(data->win_ptr, 5, 0, mouse_release, data);
	mlx_hook(data->win_ptr, 6, 0, mouse_move, data);
	mlx_hook(data->win_ptr, 12, 0, expose, data);
	mlx_hook(data->win_ptr, 17, 0, x_press, data);

	mlx_loop(data->mlx_ptr);
	return (0);
}
