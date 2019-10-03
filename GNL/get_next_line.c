/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 18:05:17 by mcamila           #+#    #+#             */
/*   Updated: 2019/10/03 16:08:53 by mcamila          ###   ########.fr       */
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
//	while (*s == '\n')
//		s++;
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
		while (s[i] == '\n')
			i++;
		if (!(buf = ft_strdup(&(s[i]))))
			return (-1);
//		buf = ft_strcpy(buf, &s[i]);
		free(s);
		list->content = buf;
//		ft_putendl(list->content);
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

static int		ft_read_to_buf(t_list **head, int fd, char **line)
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
//		ft_putnbr(rd);
//		if (list->content)
//			ft_putendl(list->content);
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
			buf2 = NULL;
			if (!(list->content))
				return (-1);
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

	if (!head)
	{
		if (!(head = (t_list **)malloc(sizeof(t_list *))))
			return (-1);
		*head = NULL;
	}
	return (ft_read_to_buf(head, fd, line));
}


//#include <sys/types.h>
//#include <sys/stat.h>
//#include <fcntl.h>
//#include <assert.h>
//
//int	main()
//{
//	char 	*line;
//	int		out;
//	int		p[2];
//	int		fd;
//	int		gnl_ret;
//
//	out = dup(1);
//	pipe(p);
//
//	fd = 1;
//	dup2(p[1], fd);
//	write(fd, "abc\n\n", 5);
//	close(p[1]);
//	dup2(out, fd);
//
//	/* Read abc and new line */
//	gnl_ret = get_next_line(p[0], &line);
//	if (gnl_ret == 1)
//		ft_putendl("Y!");
//	else
//		ft_putendl("NO");
//	if (strcmp(line, "abc") == 0)
//		ft_putendl("Y!");
//	else
//		ft_putendl("NO");
//
//	/* Read new line */
//	gnl_ret = get_next_line(p[0], &line);
//
//	if (gnl_ret == 1)
//		ft_putendl("Y!");
//	else
//		ft_putendl("NO");
//	if (line == NULL || *line == '\0')
//		ft_putendl("Y!");
//	else
//		ft_putendl("NO");
//
//	/* Read again, but meet EOF */
//	gnl_ret = get_next_line(p[0], &line);
//	if (gnl_ret == 0)
//		ft_putendl("Y!");
//	else
//		ft_putendl("NO");
//	if (line == NULL || *line == '\0')
//		ft_putendl("Y!");
//	else
//		ft_putendl("NO");
//
//	/* Let's do it once again */
//	gnl_ret = get_next_line(p[0], &line);
//	if (gnl_ret == 0)
//		ft_putendl("Y!");
//	else
//		ft_putendl("NO");
//	if (line == NULL || *line == '\0')
//		ft_putendl("Y!");
//	else
//		ft_putendl("NO");
//	return (0);
// /*
//	int fd;
//	int rd;
//	char *line;
//	char buf[BUFF_SIZE];
//
//	fd = open("123", O_RDONLY);
////	rd = read(fd, buf, BUFF_SIZE);
////	buf[rd] = '\0';
////	ft_putstr(buf);
//	while ((rd = get_next_line(fd, &line)) == 1)
//	{
////		ft_putnbr(rd);
////		ft_putchar(' ');
//		ft_putendl(line);
////		ft_putchar('0');
//		free(line);
//	}
//return (0);
//}