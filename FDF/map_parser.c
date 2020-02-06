/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 12:18:34 by mcamila           #+#    #+#             */
/*   Updated: 2020/02/07 00:24:04 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <fcntl.h>

void	error()
{
	ft_putendl("ERROR");
	exit(0);
}

t_ref_obj	make_ref_obj_from_map(int **map, int x, int y)
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
			if (map[j][i] == 0)
				col.ARGB = 0x0000FFFF;
			else
				col.ARGB = 0x00FFFF00;
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
	char **line;
	char *big_line;
	char *temp;
	char ***big_map;
	int **map;

	if ((fd = open(file_name, O_RDONLY)) < 0)
		error();
	line = (char**)malloc(sizeof(char*));
	big_line = (char*)malloc(sizeof(char));
	*big_line = '\0';
	y = 0;
	while (get_next_line(fd, line))
	{
		temp = ft_strjoin(big_line, *line);
		free(big_line);
		big_line = temp;
		temp = ft_strjoin(big_line, "/");;
		free(big_line);
		big_line = temp;
		free(*line);
		y++;
	}
	free(line);
	line = ft_strsplit(big_line, '/');

	y = 0;
	while (line[y])
		y++;

	big_map = (char***)malloc(sizeof(char**) * y);
	int i = 0;
	while (i < y)
	{
		big_map[i] = ft_strsplit(line[i], ' ');
		i++;
	}
	x = 0;
	while (big_map[0][x])
		x++;

	map = (int**)malloc(sizeof(int*) * y);

	i = 0;
	while (i < y)
	{
		map[i] = (int*)malloc(sizeof(int) * x);
		i++;
	}

	i = 0;
	while (i < y)
	{
		x = 0;
		while (big_map[i][x])
		{
			map[i][x] = ft_atoi(big_map[i][x]);
			free(big_map[i][x]);
			x++;
		}
		free(big_map[i]);
		i++;
	}
	free(big_map);

	t_ref_obj obj = make_ref_obj_from_map(map, x, y);

	return (obj);
}