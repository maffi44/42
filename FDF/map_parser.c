/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 12:18:34 by mcamila           #+#    #+#             */
/*   Updated: 2020/02/19 18:00:50 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <fcntl.h>

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

void		*pmalloc(t_data *data, t_maps *maps, size_t size)
{
	void *memory;

	if (!(memory = malloc(size)))
		error(1, data, maps);
	return (memory);
}

void	make_tri_1(t_tri *tri, int i, int j, int x)
{
	tri->pt[0] = (j * x) + i + 1;
	tri->pt[1] = (j * x) + i;
	tri->pt[2] = ((j + 1) * x) + i;
}

void	make_tri_2(t_tri *tri, int i, int j, int x)
{
	tri->pt[0] = ((j + 1) * x) + i + 1;
	tri->pt[1] = (j * x) + i + 1;
	tri->pt[2] = ((j + 1) * x) + i;
}

void	make_tri_3(t_tri *tri, int i, int j, int x)
{
	tri->pt[0] = (j * x) + i + 1;
	tri->pt[1] = (j * x) + i;
	tri->pt[2] = ((j + 1) * x) + i + 1;
}

void	make_tri_4(t_tri *tri, int i, int j, int x)
{
	tri->pt[0] = ((j + 1) * x) + i + 1;
	tri->pt[1] = (j * x) + i;
	tri->pt[2] = ((j + 1) * x) + i;
}

void	make_tris(t_ref_obj *obj, t_maps *maps, int x, int y)
{
	int i;
	int j;
	int k;

	k = 0;
	j = -1;
	while (++j < y - 1)
	{
		i = -1;
		while (++i < x - 1)
		{
			if (abs(maps->map[j][i] - maps->map[j + 1][i + 1])
				>= abs(maps->map[j + 1][i] - maps->map[j][i + 1]))
			{
				make_tri_1(&(obj->tri[k]), i, j, x);
				make_tri_2(&(obj->tri[k + 1]), i, j, x);
			}
			else
			{
				make_tri_3(&(obj->tri[k]), i, j, x);
				make_tri_4(&(obj->tri[k + 1]), i, j, x);
			}
			k += 2;
		}
	}
}

void	make_vertexes(t_ref_obj *obj, t_maps *maps, int x, int y)
{
	t_color		col;
	int			i;
	int			j;
	int			k;

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
			obj->vertex[k] = make_vertex((float)(i - x / 2),
					((float)maps->map[j][i]) / 5, (float)(j - y / 2), col.ARGB);
			k++;
		}
	}
}

t_ref_obj	make_ref_obj_from_map(int x, int y, t_data *data, t_maps *maps)
{
	t_ref_obj	obj;

	obj.num_of_pts = x * y;
	obj.num_of_tris = (x - 1) * (y - 1) * 2;
	obj.vertex = (t_vec3*)pmalloc(data, maps, sizeof(t_vec3) * obj.num_of_pts);
	obj.tri = (t_tri*)pmalloc(data, maps, sizeof(t_tri) * obj.num_of_tris);
	make_vertexes(&obj, maps, x, y);
	make_tris(&obj, maps, x, y);
	del_maps(maps);
	return (obj);
}

void	make_big_line(t_maps *maps, t_data *data)
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

void	make_big_map(t_maps *maps, t_data *data, int y)
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
		error(y, data, maps);
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
