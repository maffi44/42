/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 13:15:55 by mcamila           #+#    #+#             */
/*   Updated: 2019/09/21 22:47:38 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_makenbr(const char *s, long long nb, int pos)
{
	while (*s >= '0' && *s <= '9')
	{
		nb = nb * 10 + (*s - '0');
		s++;
	}
	return ((int)nb * pos);
}

int			ft_atoi(const char *s)
{
	int			pos;

	while (*s == '\n' || *s == '\t' || *s == '\r' ||
	*s == '\f' || *s == '\v' || *s == ' ')
		s++;
	pos = 1;
	if (*s == '-')
	{
		s++;
		pos = -1;
	}
	else
	{
		if (*s == '+')
			s++;
	}
	return (ft_makenbr(s, 0, pos));
}
