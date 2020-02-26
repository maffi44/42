/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 05:12:04 by mcamila           #+#    #+#             */
/*   Updated: 2020/02/26 07:54:14 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	go_away(t_data *data)
{
	if (data)
	{
		if (data->mlx_ptr && data->img_ptr)
			mlx_destroy_image(data->mlx_ptr, data->img_ptr);
		if (data->mlx_ptr)
			free(data->mlx_ptr);
		if (data->win_ptr)
			free(data->win_ptr);
		free(data);
	}
	exit(0);
}

void	opencl_debuger(t_opencl *opencl)
{
	char		buffer[1000];

	clGetProgramBuildInfo(opencl->program, opencl->dev_id, CL_PROGRAM_BUILD_LOG
			, 1000, buffer, NULL);
	write(1, buffer, ft_strlen(buffer));
}

void	error(t_data *data)
{
	ft_putendl("fractol: Must specify one of man, man2, jul, f1, f2, f3, f4");
	go_away(data);
}

int		ft_render(t_data *data)
{
	cl_run_kernel(data->opencl, data);
	data->p.col = color_loop(3, data->p.col);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
	return (0);
}
