/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 16:21:28 by mcamila           #+#    #+#             */
/*   Updated: 2020/02/26 07:48:49 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int			mouse_release(int button, int x, int y, t_data *data)
{
	x = y;
	if (button == 3)
	{
		((t_data *)data)->p.m_bool = 0;
		((t_data *)data)->p.sc_bool = 0;
	}
	ft_render(data);
	return (0);
}

int			mouse_move(int x0, int y0, t_data *data)
{
	int x;
	int y;

	if (data->p.jul_bool)
	{
		data->p.k_re = (x0 - (float)WIDTH / 2) * 4 / WIDTH;
		data->p.k_im = (y0 - (float)HIEGHT / 2) * 4 / HIEGHT;
	}
	if (((t_data*)data)->p.m_bool)
	{
		x = x0 - data->p.x;
		y = y0 - data->p.y;
		data->p.re_off -= (float)x * (4 * data->p.sc / WIDTH);
		data->p.im_off += (float)y * (4 * data->p.sc / HIEGHT);
		data->p.x = x0;
		data->p.y = y0;
	}
	ft_render(data);
	return (0);
}

void		inicializate_data(t_data *data)
{
	if (!(data->mlx_ptr = mlx_init()))
		go_away(data);
	if (!(data->win_ptr = mlx_new_window(data->mlx_ptr,
			WIDTH, HIEGHT, "fractal")))
		go_away(data);
	if (!(data->img_ptr = mlx_new_image(data->mlx_ptr, WIDTH, HIEGHT)))
		go_away(data);
	data->img_data = mlx_get_data_addr(data->img_ptr, &(data->p.bpp),
			&(data->p.img_line), &(data->p.endian));
	data->p.k_re = 0;
	data->p.k_im = 0;
	data->p.fract = 1;
	data->p.sc = 1;
	data->p.max_iteration = 70;
	data->p.re_off = 0;
	data->p.im_off = 0;
	data->p.m_bool = 0;
	data->p.sc_bool = 0;
	data->p.col.argb = 0x00FF00FF;
	data->p.jul_bool = 1;
}

void		inicializate_fractol(t_data *data, char *str)
{
	if ((ft_strcmp(str, "man")) == 0)
		data->p.fract = 0;
	else if (((ft_strcmp(str, "man2")) == 0))
		data->p.fract = 1;
	else if (((ft_strcmp(str, "jul")) == 0))
		data->p.fract = 2;
	else if (((ft_strcmp(str, "f1")) == 0))
		data->p.fract = 3;
	else if (((ft_strcmp(str, "f2")) == 0))
		data->p.fract = 4;
	else if (((ft_strcmp(str, "f3")) == 0))
		data->p.fract = 5;
	else if (((ft_strcmp(str, "f4")) == 0))
		data->p.fract = 6;
	else
		error(data);
}

int			main(int argc, char **argv)
{
	t_data		*data;

	data = NULL;
	if (argc != 2)
		error(data);
	if (!(data = (t_data*)malloc(sizeof(t_data))))
		go_away(data);
	inicializate_data(data);
	inicializate_fractol(data, argv[1]);
	data->opencl = init_opencl(data->opencl);
	cl_create_program(data->opencl);
	cl_init_params(data->opencl, data);
	ft_render(data);
	mlx_mouse_hook(data->win_ptr, mouse_press, (void*)data);
	mlx_hook(data->win_ptr, 2, 0, key_press, (void*)data);
	mlx_hook(data->win_ptr, 3, 0, key_release, (void*)data);
	mlx_hook(data->win_ptr, 4, 0, mouse_press, (void*)data);
	mlx_hook(data->win_ptr, 5, 0, mouse_release, (void*)data);
	mlx_hook(data->win_ptr, 6, 0, mouse_move, (void*)data);
	mlx_hook(data->win_ptr, 17, 0, x_press, data);
	mlx_loop_hook(data->mlx_ptr, ft_render, (void*)data);
	mlx_loop(data->mlx_ptr);
	return (0);
}
