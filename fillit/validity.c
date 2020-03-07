/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjasper <bjasper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 17:29:19 by mcamila           #+#    #+#             */
/*   Updated: 2019/11/17 17:02:20 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static void		ft_coordinates(int *a)
{
	int i;

	i = 0;
	while (i < 4)
	{
		a[i] = a[i] / 5 * 10 + a[i] % 5;
		++i;
	}
}

static void		ft_upp(int *a)
{
	int i;

	while (a[0] % 5 != 0 && a[1] % 5 != 0 && a[2] % 5 != 0 && a[3] % 5 != 0)
	{
		i = 0;
		while (i < 4)
		{
			a[i] -= 1;
			++i;
		}
	}
	while (a[0] > 3 && a[1] > 3 && a[2] > 3 && a[3] > 3)
	{
		i = 0;
		while (i < 4)
		{
			a[i] -= 5;
			++i;
		}
	}
}

/*
** Check connections between sharps
*/

static int		ft_is_figure_valid(char *buf, int i)
{
	int connect;

	connect = 0;
	if (buf[i - 1] == '#')
		++connect;
	if (buf[i - 5] == '#')
		++connect;
	return (connect);
}

/*
** check validity of input tetrominos. If invalid - return 0.
*/

static int		ft_letter(int *connect, char *buf, t_fill *figure, int tetnum)
{
	int ret;
	int i;

	*connect = 0;
	i = 0;
	ret = 0;
	while (i < 20)
	{
		if ((buf[i] == '.' && (i + 1) % 5 != 0) ||
		(buf[i] == '\n' && (i + 1) % 5 == 0))
			++i;
		else if (buf[i++] == '#' && i % 5 != 0 && ret < 4)
		{
			figure[tetnum].sharp[ret] = i - 1;
			*connect = *connect + ft_is_figure_valid(buf, i - 1);
			++ret;
		}
		else
			return (0);
	}
	return (ret);
}

int				ft_validity(int fd, char *buf, t_fill *figure)
{
	int ret;
	int tetnum;
	int connect;
	int sum;

	tetnum = 0;
	sum = 0;
	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		sum += ret;
		if (ret < 20 || (ret == 21 && buf[20] != '\n') || tetnum > 26)
			return (0);
		if (ft_letter(&connect, buf, figure, tetnum) != 4 ||
		(connect != 3 && connect != 4))
			return (0);
		ft_upp(figure[tetnum].sharp);
		ft_coordinates(figure[tetnum].sharp);
		ft_length(&figure[tetnum]);
		++tetnum;
	}
	if (sum % 21 == 0)
		return (0);
	return (tetnum);
}
