/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 18:05:17 by mcamila           #+#    #+#             */
/*   Updated: 2019/10/11 14:02:59 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
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

static t_list	*ft_get_list(int fd, t_list **head)
{
	t_list *list;

	if (!(list = ft_seeklst(fd, *head)))
	{
		if (!(list = (t_list*)malloc(sizeof(t_list))))
			return (NULL);
		list->content = NULL;
		list->content_size = fd;
		list->next = NULL;
		ft_lstadd(head, list);
	}
	return (list);
}

static int		ft_seek_line(char *s, int rd, char **line, t_list *list)
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
			list->content = NULL;
			return (1);
		}
		if (s[i] == '\n')
			i++;
		if (!(buf = ft_strdup(&(s[i]))))
			return (-1);
		free(s);
		list->content = buf;
		return (1);
	}
	if (rd == 0 && ft_strlen(s) == 0)
	{
		if (s)
			free(s);
		list->content = NULL;
		return (2);
	}
	return (0);
}

static int		ft_read_to_buf(t_list *list, int fd, char **line)
{
	char	buf[BUFF_SIZE + 1];
	char	*buf2;
	int		rd;

	while (1)
	{
		if ((rd = read(fd, buf, BUFF_SIZE)) == -1)
			return (-1);
		buf[rd] = '\0';
		if (list->content || rd > 0)
		{
			buf2 = NULL;
			if (!(buf2 = ft_strjoin(list->content, buf)))
				return (-1);
			free(list->content);
			list->content = buf2;
			if ((rd = ft_seek_line(list->content, rd, line, list)) != 0)
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
	static t_list	**head;
	t_list			*list;

	if (!head)
	{
		if (!(head = (t_list **)malloc(sizeof(t_list *))))
			return (-1);
		*head = NULL;
	}
	if (!(list = ft_get_list(fd, head)))
		return (-1);
	return (ft_read_to_buf(list, fd, line));
}
