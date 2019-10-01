/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 18:05:17 by mcamila           #+#    #+#             */
/*   Updated: 2019/10/01 12:56:08 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static t_list	*ft_seeklst(int fd, t_list *list)
{
	if (!list)
		return (NULL);
	if ((int)(list->content_size) == fd)
		return (list);
	return (ft_seeklst(fd, list->next));
}

static t_list	*ft_get_list(int fd, t_list *head)
{
	t_list *list;

	if (!(list = ft_seeklst(fd, head)))
	{
		if (!(list = (t_list*)malloc(sizeof(t_list))))
			return (NULL);
		list->content = NULL;
		list->content_size = fd;
		ft_lstadd(&head, list);
	}
	return (list);
}
static int		ft_seek_line(char *s, int rd, char **line)
{
	size_t	i;
	size_t	len;

	len = ft_strlen(s);
	i = 0;
	while (s[i] != '\n' && i < len)
		i++;
	if (s[i] == '\n' || (rd == 0 && ft_strlen(s) > 0))
	{
		if (!(*line = (char*)malloc(i + 1)))
			return (-1);
		*line = ft_strncpy(*line, s, i);
		(*line)[i] = '\0';
		free(s);
		return (1);
	}
	return (0);
}

static int		ft_read_to_buf(t_list *head, int fd, char **line)
{
	t_list	*list;
	char	buf[BUFF_SIZE];
	char 	*buf2 = NULL;
	int 	rd;

	if (!(list = ft_get_list(fd, head)))
		return (-1);
	while (1)
	{
		if ((rd = read(fd, buf, BUFF_SIZE)) == -1)
			return (-1);
		buf[rd] = '\0';
		if (list->content || rd > 0)
		{
			if (list->content)
				if (!(buf2 = ft_strdup(list->content)))
					return (-1);
			list->content = ft_strjoin(buf2, buf);
			ft_putstr(list->content);
			if (buf2)
				free(buf2);
			if (!(list->content))
				return (-1);
			if ((rd = ft_seek_line(list->content, rd, line)) != 0)
				return (rd);
		}
		else
			return (0);
	}
}

int				get_next_line(const int fd, char **line)
{
	static t_list	*head;

	if (!head)
	{
		if (!(head = (t_list*)malloc(sizeof(t_list))))
			return (-1);
		head->content = NULL;
		head->content_size = fd;
	}
	return (ft_read_to_buf(head, fd, line));
}

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int	main()
{
	int fd;
	int rd;
	char *line;
	char buf[BUFF_SIZE];

	fd = open("123", O_RDONLY);
//	rd = read(fd, buf, BUFF_SIZE);
//	buf[rd] = '\0';
//	ft_putstr(buf);
	while ((rd = get_next_line(fd, &line)) == 1)
	{
//		ft_putnbr(rd);
//		ft_putchar(' ');
		ft_putstr(line);
		ft_putchar('\n');
		free(line);
	}
	return (0);
}