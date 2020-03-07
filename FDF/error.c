/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 05:12:04 by mcamila           #+#    #+#             */
/*   Updated: 2020/02/22 05:36:15 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void		go_away(t_data *data)
{
	if (data)
	{
		if (data->mlx_ptr && data->img_ptr)
			mlx_destroy_image(data->mlx_ptr, data->img_ptr);
		if (data->zbuff)
			free(data->zbuff);
		if (data->obj_inst)
		{
			if (data->obj_inst->ref_obj)
			{
				if (data->obj_inst->ref_obj->tri)
					free(data->obj_inst->ref_obj->tri);
				if (data->obj_inst->ref_obj->vertex)
					free(data->obj_inst->ref_obj->vertex);
			}
			free(data->obj_inst);
		}
		if (data->mlx_ptr)
			free(data->mlx_ptr);
		if (data->win_ptr)
			free(data->win_ptr);
		free(data);
	}
	exit(0);
}

void		*pmalloc(t_data *data, t_maps *maps, size_t size)
{
	void *memory;

	if (!(memory = malloc(size)))
		error(1, data, maps);
	return (memory);
}

void		del_big_map(t_maps *maps)
{
	int i;
	int j;

	if (maps->big_map)
	{
		i = -1;
		while ((maps->big_map)[++i])
		{
			j = -1;
			while ((maps->big_map)[i][++j])
				ft_memdel(((void*)&((maps->big_map)[i][j])));
			ft_memdel(((void*)&(maps->big_map)[i]));
		}
		ft_memdel(((void*)&(maps->big_map)));
	}
}

void		del_maps(t_maps *maps)
{
	int	i;

	if (maps->temp)
		ft_memdel((void*)&(maps->temp));
	if (maps->big_line)
		ft_memdel((void*)&(maps->big_line));
	if (maps->map)
	{
		i = -1;
		while ((maps->map)[++i])
			ft_memdel(((void*)&(maps->map)[i]));
		ft_memdel((void*)&(maps->map));
	}
	if (maps->line)
	{
		i = -1;
		while ((maps->line)[++i])
			ft_memdel((void*)&(maps->line)[i]);
		ft_memdel((void*)&(maps->line));
	}
	del_big_map(maps);
}

void		error(int error, t_data *data, t_maps *maps)
{
	if (error == 0)
		ft_putendl("usage: ./fdf [filename]");
	else if (error == 1)
		ft_putendl("ERROR: memory allocate fail");
	else
		ft_putendl("ERROR: invalid map");
	if (maps)
		del_maps(maps);
	go_away(data);
}
