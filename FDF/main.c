/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 16:21:28 by mcamila           #+#    #+#             */
/*   Updated: 2020/01/13 20:26:17 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	key_press(int key, void *data)
{
	if (key == 53)
		go_away(data);
	ft_putnbr(key);
//	printf("%d", key);
//	write(1, "X", 1);
	return (0);
}

int	key_release(int key, void *param)
{
	ft_putnbr(key);
	return (0);
}

int mouse_press(int button, int x, int y, void *data)
{
	if (button == 1)
		((t_data*)data)->mouse_bool = 1;
	return (0);
}

int	mouse_release(int button, int x, int y, void *data)
{
	if (button == 1)
	{
		((t_data *) data)->mouse_bool = 0;
		write(1, "D", 1);
	}
	return (0);
}

int	mouse_move(int x, int y, void *data)
{
	if (((t_data*)data)->mouse_bool)
		mlx_pixel_put(((t_data*)data)->mlx_ptr, ((t_data*)data)->win_ptr, x, y, 99999999);
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

	mlx_hook(data->win_ptr, 2, 0, &key_press, data);
	mlx_hook(data->win_ptr, 3, 0, &key_release, (void*)0);
	mlx_hook(data->win_ptr, 4, 0, &mouse_press, data);
	mlx_hook(data->win_ptr, 5, 0, &mouse_release, data);
	mlx_hook(data->win_ptr, 6, 0, &mouse_move, data);
	mlx_hook(data->win_ptr, 17, 0, &x_press, data);

	mlx_loop(data->mlx_ptr);
	return (0);
}