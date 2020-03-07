/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 12:18:34 by mcamila           #+#    #+#             */
/*   Updated: 2020/02/22 07:30:19 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <fcntl.h>

void		make_big_line(t_maps *maps, t_data *data)
{
	if (!((maps->temp) = ft_strjoin((maps->big_line), *(maps->line))))
		error(1, data, maps);
	ft_memdel((void*)&(maps->big_line));
	(maps->big_line) = (maps->temp);
	if (!((maps->temp) = ft_strjoin((maps->big_line), "/")))
		error(1, data, maps);
	ft_memdel((void*)&(maps->big_line));
	(maps->big_line) = (maps->temp);
	maps->temp = NULL;
	ft_memdel((void*)&*(maps->line));
}

void		make_big_map(t_maps *maps, t_data *data, int y)
{
	int i;
	int x;
	int b;
	int k;

	i = -1;
	while (++i < y + 1)
		(maps->big_map)[i] = NULL;
	i = 0;
	x = 0;
	b = 0;
	while (i < y)
	{
		if (!((maps->big_map)[i] = ft_strsplit((maps->line)[i], ' ')))
			error(1, data, maps);
		k = 0;
		while ((maps->big_map)[i][k])
			k++;
		if ((x != k && b) || k == 1)
			error(2, data, maps);
		x = k;
		b = 1;
		i++;
	}
}

int			read_file(t_maps *maps, t_data *data, int x)
{
	int rd;
	int y;

	y = 0;
	while ((rd = get_next_line(x, (maps->line))) > 0)
	{
		if (ft_strlen(*(maps->line)) == 0)
			break ;
		make_big_line(maps, data);
		y++;
	}
	if (rd < 0 || ft_strlen((maps->big_line)) == 0 || y <= 1)
		error(2, data, NULL);
	ft_memdel((void*)&(maps->line));
	if (!((maps->line) = ft_strsplit((maps->big_line), '/')))
		error(1, data, maps);
	ft_memdel((void*)&(maps->big_line));
	(maps->big_map) = (char***)pmalloc(data, maps, sizeof(char**) * (y + 1));
	make_big_map(maps, data, y);
	(maps->map) = (int**)pmalloc(data, maps, sizeof(int*) * (y + 1));
	(maps->map)[y] = NULL;
	return (y);
}

int			make_int_map(t_maps *maps, t_data *data, int y)
{
	int x;
	int i;

	x = 0;
	while ((maps->big_map)[0][x])
		x++;
	i = -1;
	while (++i < y)
		(maps->map)[i] = (int*)pmalloc(data, maps, sizeof(int) * x);
	i = -1;
	while (++i < y)
	{
		x = -1;
		while ((maps->big_map)[i][++x])
			(maps->map)[i][x] = ft_atoi((maps->big_map)[i][x]);
	}
	return (x);
}

t_ref_obj	make_ref_obj(char *file_name, t_data *data)
{
	int		y;
	int		x;
	t_maps	maps;

	maps.big_line = NULL;
	maps.big_map = NULL;
	maps.line = NULL;
	maps.map = NULL;
	maps.temp = NULL;
	if ((x = open(file_name, O_RDONLY)) < 0)
		error(0, data, &maps);
	(maps.line) = (char**)pmalloc(data, &maps, sizeof(char*));
	(maps.big_line) = (char*)pmalloc(data, &maps, sizeof(char));
	*(maps.big_line) = '\0';
	*(maps.line) = NULL;
	y = read_file(&maps, data, x);
	x = make_int_map(&maps, data, y);
	return (make_ref_obj_from_map(x, y, data, &maps));
}
