/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 12:18:34 by mcamila           #+#    #+#             */
/*   Updated: 2020/02/19 11:59:44 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <fcntl.h>

void		del_maps(t_maps *maps)
{
	int	i;
	int	j;

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

void		*super_malloc(t_data *data, t_maps *maps, size_t size)
{
	void *memory;

	if (!(memory = malloc(size)))
		error(1, data, maps);
	return (memory);
}

t_ref_obj	make_ref_obj_from_map(int x, int y, t_data *data, t_maps *maps)
{
	t_ref_obj	obj;
	t_color		col;
	int			i;
	int			j;
	int			k;

	obj.num_of_pts = x * y;
	obj.num_of_tris = (x - 1) * (y - 1) * 2;
	obj.vertex = (t_vec3*)super_malloc(data, maps, sizeof(t_vec3) * obj.num_of_pts);
	obj.tri = (t_tri*)super_malloc(data, maps, sizeof(t_tri) * obj.num_of_tris);
	k = 0;
	col.ARGB = 0;
	j = -1;
	while (++j < y)
	{
		i = -1;
		while (++i < x)
		{
			col.colors[0] = maps->map[j][i] * 4;
			col.colors[1] = maps->map[j][i] * 1;
			col.colors[2] = maps->map[j][i] * 13;
			obj.vertex[k] = make_vertex((float)(i - x / 2), ((float)maps->map[j][i]) / 5, (float)(j - y / 2), col.ARGB);
			k++;
		}
	}
	k = 0;
	j = -1;
	while (++j < y - 1)
	{
		i = -1;
		while (++i < x - 1)
		{
			if (abs(maps->map[j][i] - maps->map[j + 1][i + 1]) >= abs(maps->map[j + 1][i] - maps->map[j][i + 1]))
			{
				obj.tri[k].pt[0] = (j * x) + i + 1;
				obj.tri[k].pt[1] = (j * x) + i;
				obj.tri[k].pt[2] = ((j + 1) * x) + i;
				obj.tri[k + 1].pt[0] = ((j + 1) * x) + i + 1;
				obj.tri[k + 1].pt[1] = (j * x) + i + 1;
				obj.tri[k + 1].pt[2] = ((j + 1) * x) + i;
			}
			else
			{
				obj.tri[k].pt[0] = (j * x) + i + 1;
				obj.tri[k].pt[1] = (j * x) + i;
				obj.tri[k].pt[2] = ((j + 1) * x) + i + 1;
				obj.tri[k + 1].pt[0] = ((j + 1) * x) + i + 1;
				obj.tri[k + 1].pt[1] = (j * x) + i;
				obj.tri[k + 1].pt[2] = ((j + 1) * x) + i;
			}
			k += 2;
		}
	}
	del_maps(maps);
	return (obj);
}

t_ref_obj	map_parser(char *file_name, t_data *data)
{
	int		fd;
	int		y;
	int		x;
	int		rd;
	t_maps	maps;

	maps.big_line = NULL;
	maps.big_map = NULL;
	maps.line = NULL;
	maps.map = NULL;
	maps.temp = NULL;
	if ((fd = open(file_name, O_RDONLY)) < 0)
		error(0, data, &maps);
	(maps.line) = (char**)super_malloc(data, &maps, sizeof(char*));
	(maps.big_line) = (char*)super_malloc(data, &maps, sizeof(char));
	*(maps.big_line) = '\0';
	*(maps.line) = NULL;
	y = 0;
	while ((rd = get_next_line(fd, (maps.line))) > 0)
	{
		if (ft_strlen(*(maps.line)) == 0)
			break;
		if (!((maps.temp) = ft_strjoin((maps.big_line), *(maps.line))))
			error(1, data, &maps);
		ft_memdel((void*)&(maps.big_line));
		(maps.big_line) = (maps.temp);
		if (!((maps.temp) = ft_strjoin((maps.big_line), "/")))
			error(1, data, &maps);
		ft_memdel((void*)&(maps.big_line));
		(maps.big_line) = (maps.temp);
		maps.temp = NULL;
		ft_memdel((void*)&*(maps.line));
		y++;
	}
	if (rd < 0 || ft_strlen((maps.big_line)) == 0 || y <= 1)
		error(y, data, &maps);
	ft_memdel((void*)&(maps.line));
	if (!((maps.line) = ft_strsplit((maps.big_line), '/')))
		error(1, data, &maps);
	ft_memdel((void*)&(maps.big_line));
	(maps.big_map) = (char***)super_malloc(data, &maps, sizeof(char**) * (y + 1));
	(maps.big_map)[y] = NULL;
	int i = 0;
	int k;
	x = 0;
	int b = 0;
	while (i < y)
	{
		if (!((maps.big_map)[i] = ft_strsplit((maps.line)[i], ' ')))
			error(1, data, &maps);
		k = 0;
		while ((maps.big_map)[i][k])
			k++;
		if ((x != k && b) || k == 1)
			error(2, data, &maps);
		x = k;
		b = 1;
		i++;
	}
	(maps.map) = (int**)super_malloc(data, &maps, sizeof(int*) * (y + 1));
	(maps.map)[y] = NULL;
	x = -1;
	while ((maps.big_map)[0][++x]);
	i = -1;
	while (++i < y)
	(maps.map)[i] = (int*)super_malloc(data, &maps, sizeof(int) * x);
	i = -1;
	while (++i < y)
	{
		x = -1;
		while ((maps.big_map)[i][++x])
			(maps.map)[i][x] = ft_atoi((maps.big_map)[i][x]);
	}
	return (make_ref_obj_from_map(x, y, data, &maps));
}
