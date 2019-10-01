/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 18:05:17 by mcamila           #+#    #+#             */
/*   Updated: 2019/10/01 11:48:11 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_list	*ft_seeklst(int fd, t_list *list)
{
	if (!list)
		return (NULL);
	if (list->content_size == fd)
		return (t_list);
	ft_seeklist(fd, list->next);
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
		ft_lstadd(head, list);
	}
	return (list);
}
int				ft_seek_line(char *s, int rd, char **line)
{
	size_t	i;

	i = 0;
	while (s[i] != '\n' && s[i] != '\0')
		i++;
	if (s[i] == '\n' || (rd == 0 && ft_strlen(s) > 0))
	{
		if (!(*line = (char*)malloc(i + 1)))
			return (-1);
		*line = ft_strncpy(s, i);
		(*line)[i] = '\0';
		free(s);
		return (1)
	}
	return (0);
}

int				ft_read_to_buf(t_list **head, int fd, char **line)
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
		if (list->content || rd > 0)
		{
			if (list->content)
				if (!(buf2 = ft_strdup(list->content)))
					return (-1);
			list->content = ft_strjoin(buf2, buf);
			if (buf)
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
		head = ft_lstnew("", 1);
	if (!head)
		return (-1);
	return (ft_read_to_buf(head, fd, line));
}
