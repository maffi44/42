/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 11:37:16 by mcamila           #+#    #+#             */
/*   Updated: 2020/02/26 00:50:57 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
//
//t_complex	init_complex(float re, float im)
//{
//	t_complex c;
//
//	c.re = re;
//	c.im = im;
//	return (c);
//}
//
//t_complex	julia(t_complex z, t_complex c)
//{
//	z = init_complex(z.re * z.re - z.im * z.im + c.re,
//					 2.0f * z.re * z.im + c.im);
//	return (z);
//}
//
//t_complex	mandelbar_2(t_complex z, t_complex c)
//{
//	z = init_complex(z.re * z.re - z.im * z.im + c.re,
//			-2.0f * z.re * z.im + c.im);
//	return (z);
//}
//
//t_complex	mandelbar(t_complex z, t_complex c)
//{
//	z = init_complex(z.re * z.re - z.im * z.im + c.re,
//					 2.0f * z.re * z.im + c.im);
//	return (z);
//}
//
//void	fractol_frame(t_data *data)
//{
//	int y;
//	int x;
//	int max_iteration;
//	int iteration;
//	t_complex min;
//	t_complex max;
//	t_complex f;
//	t_complex c;
//	t_complex z;
//	t_color col;
//	t_complex k;
//
//	min = init_complex(-2 * data->sc + data->re_off, -2 * data->sc + data->im_off);
//	max = init_complex(2 * data->sc + data->re_off, 2 * data->sc + data->im_off);
//	f = init_complex((max.re - min.re) / (WIDTH - 1),
//			(max.im - min.im) / (HIEGHT - 1));
//	max_iteration = data->max_iteration;
//	col.argb = 0;
//	k = init_complex(data->k_re, data->k_im);
//	y = 0;
//	while (y < HIEGHT)
//	{
//		c.im = max.im - y * f.im;
//		x = 0;
//		while (x < WIDTH)
//		{
//			c.re = min.re + x * f.re;
//			z = init_complex(c.re, c.im);
//			iteration = 0;
//			while(z.re * z.re + z.im * z.im <= 4
//				&& iteration < max_iteration)
//			{
//				if (data->fract == 1)
//					z = mandelbar(z, c);
//				else if (data->fract == 2)
//					z = mandelbar_2(z, c);
//				else
//					z = julia(z, k);
//				iteration++;
//			}
//			col.colors[0] = iteration / 2 * (255 / max_iteration);
//			col.colors[1] = iteration / 10 * (255 / max_iteration);
//			col.colors[2] = iteration * (255 / max_iteration);
//			if (iteration == max_iteration)
//				col.argb = 0;
//			put_pixel(x, y, col.argb, data);
//			x++;
//		}
//		y++;
//	}
//	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
//}
