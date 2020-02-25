/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 05:12:04 by mcamila           #+#    #+#             */
/*   Updated: 2020/02/24 19:27:52 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void		go_away(t_data *data)
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
