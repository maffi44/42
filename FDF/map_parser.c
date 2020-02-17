/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 20:02:56 by mcamila           #+#    #+#             */
/*   Updated: 2020/02/17 20:02:56 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 20:02:55 by mcamila           #+#    #+#             */
/*   Updated: 2020/02/17 20:02:55 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 12:18:34 by mcamila           #+#    #+#             */
/*   Updated: 2020/02/17 20:02:52 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <fcntl.h>

typedef struct 		s_maps
{
	char **line;
	char *big_line;
	char *temp;
	char ***big_map;
	int **map;
}					t_maps;

void	del_maps(t_maps *maps)
{
	size_t i;
	size_t j;

	if (maps->temp)
		ft_memdel(&(maps->temp));
	if (maps->big_line)
		ft_memdel(&(maps->big_line));
	if (maps->map)
	{
		i = 0;
		while ((maps->map)[i])
			ft_memdel((&(maps->map)[i++]));
		ft_memdel(&(maps->map));
	}
	if (maps->line)
	{
		i = 0;
		while ((maps->line)[i])
			ft_memdel(&(maps->line)[i++]));
		ft_memdel(&(maps->line));
	}
	if (maps->big_map)
	{
		i = 0;
		while ((maps->big_map)[i])
		{
			j = 0;
			while ((maps->big_map)[i][j])
				ft_memdel((&(maps->line)[i][j++]));
			ft_memdel((&(maps->line)[i++]));
		}
		ft_memdel((&(maps->line)));
	}
}

void	error(int error, t_data *data, t_maps *maps)
{
	if (error == 0)
		ft_putendl("ERROR");
	else if (error == 1)
		;
	else
		;
	del_maps(maps);
	go_away(data);
}

t_ref_obj	make_ref_obj_from_map(int **map, int x, int y, t_data *data)
{
	t_ref_obj obj;
	int i;
	int j;
	int k;
	t_color col;

	obj.num_of_pts = x * y;
	obj.num_of_tris = (x - 1) * (y - 1) * 2;
	obj.vertex = (t_vec3*)malloc(sizeof(t_vec3) * obj.num_of_pts);
	obj.tri = (t_tri*)malloc(sizeof(t_tri) * obj.num_of_tris);

	j = 0;
	k = 0;
	col.ARGB = 0;
	while (j < y)
	{
		i = 0;
		while (i < x)
		{
			//if (map[j][i] < 5)
			//	col.ARGB = 0x0000FFFF;
			//else
			//	col.ARGB = 0x00FFFF00;
			col.colors[0] = map[j][i] * 4;
			col.colors[1] = map[j][i] * 1;
			col.colors[2] = map[j][i] * 13;
			obj.vertex[k] = make_vertex((float)(i - x / 2), ((float)map[j][i]) / 5, (float)(j - y / 2), col.ARGB);
			i++;
			k++;
		}
		j++;
	}
	j = 0;
	k = 0;
	while (j < y - 1)
	{
		i = 0;
		while (i < x - 1)
		{
			if (abs(map[j][i] - map[j + 1][i + 1]) >= abs(map[j + 1][i] - map[j][i + 1]))
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
			i++;
			k += 2;
		}
		j++;
	}
	return (obj);
}



t_ref_obj	map_parser(char *file_name)
{
	int fd;
	int y;
	int x;
	t_maps maps;

	maps.big_line = NULL;
	maps.big_map = NULL;
	maps.line = NULL;
	maps.map = NULL;
	maps.temp = NULL;

	if ((fd = open(file_name, O_RDONLY)) < 0)
		error(0);
	(maps.line) = (char**)malloc(sizeof(char*));
	(maps.big_line) = (char*)malloc(sizeof(char));
	*(maps.big_line) = '\0';
	y = 0;
	while (get_next_line(fd, (maps.line)))
	{
		(maps.temp) = ft_strjoin((maps.big_line), *(maps.line));
		ft_memdel(&(maps.big_line));
		(maps.big_line) = (maps.temp);
		(maps.temp) = ft_strjoin((maps.big_line), "/");;
		ft_memdel(&(maps.big_line));
		(maps.big_line) = (maps.temp);
		ft_memdel(&*(maps.line));
		y++;
	}
	ft_memdel(&(maps.line));
	if (ft_strlen((maps.big_line)) == 0)
		error(0);
	(maps.line) = ft_strsplit((maps.big_line), '/');
	ft_memdel(&(maps.big_line));

	y = 0;
	while ((maps.line)[y])
		y++;

	(maps.big_map) = (char***)malloc(sizeof(char**) * y);
	int i = 0;
	while (i < y)
	{
		(maps.big_map)[i] = ft_strsplit((maps.line)[i], ' ');
		ft_memdel(&(maps.line)[i]);
		i++;
	}
	ft_memdel(&(maps.line));
	x = 0;
	while ((maps.big_map)[0][x])
		x++;

	(maps.map) = (int**)malloc(sizeof(int*) * y);

	i = 0;
	while (i < y)
	{
		(maps.map)[i] = (int*)malloc(sizeof(int) * x);
		i++;
	}
	i = 0;
	while (i < y)
	{
		x = 0;
		while ((maps.big_map)[i][x])
		{
			(maps.map)[i][x] = ft_atoi((maps.big_map)[i][x]);
			ft_memdel(&(maps.big_map)[i][x]);
			x++;
		}
		ft_memdel(&(maps.big_map)[i]);
		i++;
	}
	ft_memdel(&(maps.big_map));

	t_ref_obj obj = make_ref_obj_from_map((maps.map), x, y);

	i = 0;
	while (i < y)
	{
		ft_memdel(&(maps.map)[i]);
		printf("%d\n", i + 1);
		i++;
	}
	ft_memdel(&(maps.map));
	return (obj);
}