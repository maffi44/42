/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 16:21:28 by mcamila           #+#    #+#             */
/*   Updated: 2020/01/14 10:21:23 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/Users/mcamila/MyProjects/42/42/MinilibX/minilibx_macos/mlx.h"
#include "header.h"
#include <unistd.h>

int	hui_mahui()
{
	write(1, "X", 1);
	return (0);
}

int	main() {
	void *mlx_ptr;
	void *win_ptr;

	if (!(mlx_ptr = mlx_init()))
		return (0);
	if (!(win_ptr = mlx_new_window(mlx_ptr, 1920, 1080, "hui")))
		return (0);
	mlx_pixel_put(mlx_ptr, win_ptr, 300, 300, 99999999);
	mlx_key_hook(win_ptr, hui_mahui, (void *) 0);
	mlx_loop(mlx_ptr);

	return (1);
}
