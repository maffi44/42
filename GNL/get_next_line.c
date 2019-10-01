/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 18:05:17 by mcamila           #+#    #+#             */
/*   Updated: 2019/10/01 17:21:30 by mcamila          ###   ########.fr       */
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
	char	*buf;

	i = 0;
	while (s[i] != '\n' && s[i] != '\0')
		i++;
	if (s[i] == '\n' || (rd == 0 && ft_strlen(s) > 0))
	{
		if (!(*line = (char*)malloc(i + 1)))
			return (-1);
		*line = ft_strncpy(*line, s, i);
		(*line)[i] = '\0';
		if (s[i] == '\0')
		{
			free(s);
			s = NULL;
			return (1);
		}
		i++;
		if (!(buf = ft_strnew(ft_strlen(s) - i)))
			return (-1);
		buf = ft_strcpy(buf, &s[i]);
		free(s);
		s = ft_strdup(buf);
		ft_memdel((void**)&buf);
		return (1);
	}
	if (rd == 0 && s[i] == '\0')
	{
		free(s);
		s = NULL;
		return (2);
	}
	return (0);
}

static int		ft_read_to_buf(t_list *head, int fd, char **line)
{
	t_list	*list;
	char	buf[BUFF_SIZE];
	char 	*buf2;
	int 	rd;

	if (!(list = ft_get_list(fd, head)))
		return (-1);
	while (1)
	{
		if ((rd = read(fd, buf, BUFF_SIZE)) == -1)
			return (-1);
//		ft_putnbr(fd);
//		if (list->content)
//			ft_putendl(list->content);
		if (rd == 0)
			return (0);
		buf[rd] = '\0';

		if (list->content || rd > 0)
		{
//			ft_putendl("fafafa");
			buf2 = NULL;
			if (list->content)
				if (!(buf2 = ft_strdup(list->content)))
					return (-1);
			list->content = ft_strjoin(buf2, buf);
//			if (list->content)
//				ft_putendl(list->content);
			if (buf2)
				free(buf2);
			if (!(list->content))
				return (-1);
			if ((rd = ft_seek_line(list->content, rd, line)) != 0)
			{
				if (rd == 2)
					return (0);
				return (rd);
			}
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
		ft_putendl(line);
//		ft_putchar('0');
		free(line);
	}
	return (0);
}
