/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializate_camera.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 05:05:48 by mcamila           #+#    #+#             */
/*   Updated: 2020/02/24 19:27:52 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void		initialize_rotation(t_camera *cam)
{
	cam->rotation.elem[0][0] = 1;
	cam->rotation.elem[0][1] = 0;
	cam->rotation.elem[0][2] = 0;
	cam->rotation.elem[0][3] = 0;
	cam->rotation.elem[1][0] = 0;
	cam->rotation.elem[1][1] = 1;
	cam->rotation.elem[1][2] = 0;
	cam->rotation.elem[1][3] = 0;
	cam->rotation.elem[2][0] = 0;
	cam->rotation.elem[2][1] = 0;
	cam->rotation.elem[2][2] = 1;
	cam->rotation.elem[2][3] = 0;
	cam->rotation.elem[3][0] = 0;
	cam->rotation.elem[3][1] = 0;
	cam->rotation.elem[3][2] = 0;
	cam->rotation.elem[3][3] = 1;
}

void		initialize_translation(t_camera *cam)
{
	cam->translation.elem[0][0] = 0;
	cam->translation.elem[0][1] = 0;
	cam->translation.elem[0][2] = 0;
	cam->translation.elem[0][3] = 1;
	cam->translation.elem[1][0] = 0;
	cam->translation.elem[1][1] = 0;
	cam->translation.elem[1][2] = 0;
	cam->translation.elem[1][3] = 1;
	cam->translation.elem[2][0] = 0;
	cam->translation.elem[2][1] = 0;
	cam->translation.elem[2][2] = 0;
	cam->translation.elem[2][3] = 1;
	cam->translation.elem[3][0] = 0;
	cam->translation.elem[3][1] = 0;
	cam->translation.elem[3][2] = 0;
	cam->translation.elem[3][3] = 1;
}

void		initialize_projection(t_camera *cam, float d)
{
	cam->projection.elem[0][0] = d;
	cam->projection.elem[0][1] = 0;
	cam->projection.elem[0][2] = 0;
	cam->projection.elem[0][3] = 0;
	cam->projection.elem[1][0] = 0;
	cam->projection.elem[1][1] = d;
	cam->projection.elem[1][2] = 0;
	cam->projection.elem[1][3] = 0;
	cam->projection.elem[2][0] = 0;
	cam->projection.elem[2][1] = 0;
	cam->projection.elem[2][2] = 1;
	cam->projection.elem[2][3] = 0;
	cam->projection.elem[3][0] = 1;
	cam->projection.elem[3][1] = 1;
	cam->projection.elem[3][2] = 1;
	cam->projection.elem[3][3] = 1;
}

t_camera	initialize_camera(float d)
{
	t_camera cam;

	initialize_rotation(&cam);
	initialize_translation(&cam);
	initialize_projection(&cam, d);
	return (cam);
}

inline void	put_pixel(int x, int y, int color, t_data *data)
{
	if (x >= WIDTH || x < 0 || y >= HIEGHT || y < 0)
		return ;
	((int*)(data->img_data))[x + (y * WIDTH)] = color;
}
