/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 18:05:17 by mcamila           #+#    #+#             */
/*   Updated: 2019/10/03 22:53:11 by mcamila          ###   ########.fr       */
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

static int		ft_read_to_buf(t_list **head, int fd, char **line)
{
	t_list	*list;
	char	buf[BUFF_SIZE + 1];
	char 	*buf2;
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
			buf2 = NULL;
			if (list->content)
			{
				if (!(buf2 = ft_strdup(list->content)))
					return (-1);
				free(list->content);
			}
			list->content = ft_strjoin(buf2, buf);
			if (buf2)
				free(buf2);
			if (!(list->content))
			{
				free(list->content);
				return (-1);
			}
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
/*
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
//#include "gnl.h"

int				main(void)
{
	char		*line1;
	char		*line2;
	char		*line3;
	int			fd1;
	int			fd2;
	int			fd3;
	int			ret1;
	int			ret2;
	int			ret3;
	char		*filename1;
	char		*filename2;
	int			errors;

	filename1 = "/Users/mcamila/42FileChecker/srcs/gnl/gnl11_1.txt";
	filename2 = "/Users/mcamila/42FileChecker/srcs/gnl/gnl11_2.txt";
	fd1 = open(filename1, O_RDONLY);
	fd2 = open(filename2, O_RDONLY);
	fd3 = -1;
	if (fd1 > 2 && fd2 > 2)
	{
		errors = 0;
		line1 = NULL;
		line2 = NULL;
		line3 = NULL;

		ret1 = get_next_line(fd1, &line1);
		if (ret1 != 1 || strcmp(line1, "The getdelim() function reads a line from stream, delimited by the character") != 0)
		{
			printf("-> must have returned '1' and read line #1 \"The getdelim() function reads a line from stream, delimited by the character\" from file %s\n", filename1);
			errors++;
		}

		ret1 = get_next_line(fd1, &line1);
		if (ret1 != 1 || strcmp(line1, "delimiter.  The getline() function is equivalent to getdelim() with the new-") != 0)
		{
			printf("-> must have returned '1' and read line #2 \"delimiter.  The getline() function is equivalent to getdelim() with the new-\" from file %s\n", filename1);
			errors++;
		}

		ret1 = get_next_line(fd1, &line1);
		if (ret1 != 1 || strcmp(line1, "line character as the delimiter.  The delimiter character is included as") != 0)
		{
			printf("-> must have returned '1' and read line #3 \"line character as the delimiter.  The delimiter character is included as\" from file %s\n", filename1);
			errors++;
		}

		ret1 = get_next_line(fd1, &line1);
		if (ret1 != 1 || strcmp(line1, "part of the line, unless the end of the file is reached.") != 0)
		{
			printf("-> must have returned '1' and read line #4 \"part of the line, unless the end of the file is reached.\" from file %s\n", filename1);
			errors++;
		}

		ret2 = get_next_line(fd2, &line2);
		if (ret2 != 1 || strcmp(line2, "The Festival de Radio France et Montpellier is a summer festival of opera and other music held in Montpellier.") != 0)
		{
			printf("-> must have returned '1' and read line #1 \"The Festival de Radio France et Montpellier is a summer festival of opera and other music held in Montpellier.\" from file %s\n", filename2);
			errors++;
		}

		ret2 = get_next_line(fd2, &line2);
		if (ret2 != 1 || strcmp(line2, "The festival concentrates on classical music and jazz with about 150 events, including opera, concerts, films, and talks. ") != 0)
		{
			printf("-> must have returned '1' and read line #2 \"The festival concentrates on classical music and jazz with about 150 events, including opera, concerts, films, and talks. \" from file %s\n", filename2);
			errors++;
		}

		ret2 = get_next_line(fd2, &line2);
		if (ret2 != 1 || strcmp(line2, "Most of these events are free and are held in the historic courtyards of the city or in the modern concert halls of Le Corum. ") != 0)
		{
			printf("-> must have returned '1' and read line #3 \"Most of these events are free and are held in the historic courtyards of the city or in the modern concert halls of Le Corum. \" from file %s\n", filename2);
			errors++;
		}

		ret2 = get_next_line(fd2, &line2);
		if (ret2 != 1 || strcmp(line2, "Le Corum cultural and conference centre contains 3 auditoriums. ") != 0)
		{
			printf("-> must have returned '1' and read line #4 \"Le Corum cultural and conference centre contains 3 auditoriums. \" from file %s\n", filename2);
			errors++;
		}

		ret3 = get_next_line(fd3, &line3);
		if (ret3 != -1)
		{
			printf("-> must have returned '-1' with invalid file descriptor\n");
			errors++;
		}

		ret1 = get_next_line(fd1, &line1);
		if (ret1 != 1 || strcmp(line1, "") != 0)
		{
			ft_putnbr(ret1);
			ft_putchar('\n');
			ft_putendl(line1);
			printf("-> must have returned '1' and read line #5 \"\" from file %s\n", filename1);
			errors++;
		}

		ret1 = get_next_line(fd1, &line1);
		if (ret1 != 1 || strcmp(line1, "The caller may provide a pointer to a malloced buffer for the line in") != 0)
		{
			printf("-> must have returned '1' and read line #6 \"The caller may provide a pointer to a malloced buffer for the line in\" from file %s\n", filename1);
			errors++;
		}

		ret1 = get_next_line(fd1, &line1);
		if (ret1 != 1 || strcmp(line1, "*linep, and the capacity of that buffer in *linecapp.  These functions") != 0)
		{
			printf("-> must have returned '1' and read line #7 \"*linep, and the capacity of that buffer in *linecapp.  These functions\" from file %s\n", filename1);
			errors++;
		}

		ret1 = get_next_line(fd1, &line1);
		if (ret1 != 1 || strcmp(line1, "expand the buffer as needed, as if via realloc().  If linep points to a NULL") != 0)
		{
			printf("-> must have returned '1' and read line #8 \"expand the buffer as needed, as if via realloc().  If linep points to a NULL\" from file %s\n", filename1);
			errors++;
		}

		ret1 = get_next_line(fd1, &line1);
		if (ret1 != 1 || strcmp(line1, "pointer, a new buffer will be allocated.  In either case, *linep and") != 0)
		{
			printf("-> must have returned '1' and read line #9 \"pointer, a new buffer will be allocated.  In either case, *linep and\" from file %s\n", filename1);
			errors++;
		}

		ret1 = get_next_line(fd1, &line1);
		if (ret1 != 1 || strcmp(line1, "*linecapp will be up-dated accordingly.") != 0)
		{
			printf("-> must have returned '1' and read line #10 \"*linecapp will be up-dated accordingly.\" from file %s\n", filename1);
			errors++;
		}

		ret2 = get_next_line(fd2, &line2);
		if (ret2 != 1 || strcmp(line2, "The city is a center for cultural events since there are many students. ") != 0)
		{
			printf("-> must have returned '1' and read line #5 \"The city is a center for cultural events since there are many students. \" from file %s\n", filename2);
			errors++;
		}

		ret2 = get_next_line(fd2, &line2);
		if (ret2 != 1 || strcmp(line2, "Montpellier has two large concerts venues: Le Zenith Sud (7.000 seats) and L'Arena (14.000 seats).") != 0)
		{
			printf("-> must have returned '1' and read line #6 \"Montpellier has two large concerts venues: Le Zenith Sud (7.000 seats) and L'Arena (14.000 seats).\" from file %s\n", filename2);
			errors++;
		}

		ret1 = get_next_line(fd1, &line1);
		if (ret1 != 0)
		{
			printf("-> must have returned '0' at the end of file %s\n", filename1);
			errors++;
		}

		ret2 = get_next_line(fd2, &line2);
		if (ret2 != 0)
		{
			printf("-> must have returned '0' at the end of file %s\n", filename2);
			errors++;
		}

		close(fd1);
		close(fd2);
		if (errors == 0)
			printf("OK\n");
	}
	else
		printf("An error occured while opening files %s and/or %s\n", filename1, filename2);
	return (0);
}
*/

/*
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	int fd[3];

	fd[0] = open("123", O_RDONLY);
	fd[1] = open("124", O_RDONLY);
	fd[2] = open("125", O_RDONLY);

	char *line;

	int i = 0;
	int j = 0;
	while (j < 45)
	{
		if (get_next_line(fd[i], &line) == 1)
		{
			ft_putendl(line);
			free(line);
		}
		i++;
		if (i == 3)
			i = 0;
		j++;
	}
	return (0);
}
*/
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