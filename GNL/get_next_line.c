/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 18:05:17 by mcamila           #+#    #+#             */
/*   Updated: 2019/09/28 21:11:47 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void		ft_freeclst(t_list *clist, t_list *head)
{
	if (!clist)
		return ;./
	if (clist != head)
	{
		while (head->next != clist)
			head = head->next;
		head->next = clist->next;
	}
	free(clist->content);
	free(clist);
	clist = NULL;
}

int				get_next_line(const int fd, char **line)
{
	static t_list	*list;
	t_list			*clist;
	char			buf[BUFF_SIZE];
	size_t			i;
	size_t			j;
	int 			rd;

	if (!list)
	{
		if (!(list = (t_list*)malloc(sizeof(t_list))))
			return (-1);
		list->next = NULL;
		list->content_size = 0;
	}
	if (list)
	{
		clist = ft_seeklst(fd, list);
		if (clist)
		{
			i = 0;
			while (((char*)(clist->content))[i] != '\n' || ((char*)(clist->content))[i] != '\0')
				i++;
			if (((char*)(clist->content))[i] == '\n' || ((char*)(clist->content))[i] == '\0')
			{
				if (!(*line = (char*)malloc(i + 1)))
					return (-1);
				ft_strncpy(*list, clist->content, i);
				(*list)[i] = '\0';
				return (1);
			}
		}
	}
	rd = 1;
	while (rd > 0)
	{
		rd = read(fd, buf, BUFF_SIZE);
		if (rd == -1)
			return (-1);
		if (rd == 0)
		{
			ft_freeclst(clist, list);
			return (0);
		}
		j = 0;
		while ((buf[j] != '\n' || buf[j] != '\0') && j < BUFF_SIZE)
			j++;
		if (buf[j] != '\n' || buf[j] != '\0')
		{
			if (*line = (char*)malloc(j + 1 + ft_strlen((char*)clist->content))
			{
				ft_strncpy(*line, (char*)(clist->content), ft_strlen(clist->content))
				ft_strcat(line, buf);
				free(clist->content);
				clist->content = NULL;
			}
			else
				return (-1);
			if (j < BUFF_SIZE)
			{
				clist->content = malloc(BUFF_SIZE - j + 1)
				if (clist->content == NULL)
				{
					free(*list);
					return (-1);
				}
				ft_strncpy((char *) (clist->content), &buf[j], BUFF_SIZE - j);
				return (1);
			}
		}
	}


	rd = read(fd, buf, BUFF_SIZE)

	i = 0;
	while ((buf[i] != '\n' || buf[i] != '\0') && i < BUFF_SIZE)
		i++;
	if (!(clist = ft_seeklst(fd, list)))

	if (*line = (char*)malloc(i + 1))
	{
		ft_strncpy(*line, buf, i);
		(*line)[i] = '\0';
	}
	else
		return (-1);
	if (i < BUFF_SIZE)
	{
		if (!(list.content = malloc(BUFF_SIZE - i)))
		{
			free(*line);
			return (-1);
		}
		ft_strncpy(list.content, &buf[i], BUFF_SIZE - i);
		list.content[BUFF_SIZE - i] = '\0';
		list.content_size = fd;pwd
	}
	return (-1);
}

static t_list	*ft_seeklst(int fd, t_list *list)
{
	if (!list)
		return (NULL);
	if (list->content_size == fd)
		return (t_list);
	ft_seeklist(fd, list->next);
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

int				ft_read_to_buf(t_list *list, t_list **head, int fd, char **line)
{
	char	buf[BUFF_SIZE];
	char 	*buf2;
	int 	rd;

	if (!(list = ft_seeklst(fd, head)))
	{
		list = (t_list*)malloc(sizeof(t_list));
		list->content = ft_strnew(0);
		list->content_size = fd;
		ft_lstadd(head, list);
	}
	while (1)
	{
		rd = read(fd, buf, BUFF_SIZE);
		if (rd < 0)
			return (-1);
		if (!(buf2 = ft_strdup(list->content)))
			return (-1);
		list->content = ft_strjoin(buf2, buf);
		free(buf2);
		if (!(list->content))
			return (-1);
		if (ft_seek_line(list->content, rd, line) == 1)
			return (1);
	}


}

int				get_next_line(const int fd, char **line)
{
	static t_list	*head;
	t_list			*list;

	if (!head)
		head = ft_lstnew("", 1);
	if (!head)
		return (-1);
	ft_read_to_buf(list, head, fd, line);


}
