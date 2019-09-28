/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 15:54:50 by mcamila           #+#    #+#             */
/*   Updated: 2019/09/13 15:50:48 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	while (*str != '\0')
	{
		ft_putchar(*str);
		str++;
	}
}

#define BUFF_SIZE 64

int		main(int argc, char **argv)
{
	int		descr;
	int		ret;
	char	buf[BUFF_SIZE + 1];

	if (argc > 2)
	{
		write(2, "Too many arguments.\n", 20);
		return (1);
	}
	if ((descr = open(argv[1], O_RDONLY)) == -1)
	{
		write(2, "File name missing.\n", 19);
		return (1);
	}
	while ((ret = read(descr, buf, BUFF_SIZE)))
	{
		buf[ret] = '\0';
		ft_putstr(buf);
	}
	close(descr);
	return (0);
}
