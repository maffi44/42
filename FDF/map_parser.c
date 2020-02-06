/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 12:18:34 by mcamila           #+#    #+#             */
/*   Updated: 2020/02/06 16:48:51 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <fcntl.h>

void	error()
{
	ft_putendl("ERROR");
	exit(0);
}

void	line_add_to_map(char *line, t_list **head)
{
	t_list *new;
	new = ft_lstnew((const void*)line, sizeof(line));
	ft_lstadd(head, new);
}

void 	map_parser(char *file_name)
{
	int fd;
	int i;
	int y;
	int x;
	int **map;
	char *line;
	t_list	*list;
	t_list **head;

	if ((fd = open(file_name, O_RDONLY)) < 0)
		error();
	head = (t_list**)malloc(sizeof(t_list*));
//	line = (char**)malloc(sizeof(char*));
	if (get_next_line(fd, &line))
	{
		*head = &(ft_lstnew((const void*)line, sizeof(line)));
//		free(*line);
	}
	while (get_next_line(fd, &line))
	{
		line_add_to_map(line, head);
//	free(*line);
	}
	list = *head;
	y = 0;
	while (list)
	{
		list->content = (void*)ft_strsplit((char *) (list->content), ' ');
		list = list->next;
		y++;
	}
	x = 0;
	while (((char**)((*head)->content))[x])
		x++;
	map = (int**)malloc(sizeof(int*) * y);
	fd = 0;
	list = *head;
	while (fd < y)
	{
		map[fd] = (int*)malloc(sizeof(int) * x);
		i = 0;
		while (i < x)
		{
			if (((char**)(list->content))[i])
				map[y][x] = ft_atoi(((char**)(list->content))[i]);
			else
				error();
		}
		list = list->next;
	}
	error();
}