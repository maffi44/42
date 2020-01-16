/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 16:16:54 by mcamila           #+#    #+#             */
<<<<<<< HEAD
<<<<<<< HEAD
/*   Updated: 2020/01/16 17:14:01 by mcamila          ###   ########.fr       */
=======
/*   Updated: 2020/01/14 11:51:47 by mcamila          ###   ########.fr       */
>>>>>>> parent of d2b40b7... fdf 123
=======
/*   Updated: 2020/01/14 11:51:47 by mcamila          ###   ########.fr       */
>>>>>>> parent of d2b40b7... fdf 123
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "/Users/mcamila/MyProjects/42/42/libft/libft.h"
#include "/Users/mcamila/MyProjects/42/42/MinilibX/minilibx_macos/mlx.h"

typedef struct	s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	char		mouse_bool;
}				t_data;

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

#endif /* HEADER_H */