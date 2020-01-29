/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 19:26:20 by mcamila           #+#    #+#             */
/*   Updated: 2019/09/18 11:36:55 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char	*ft_makeistr(int nb, int f, int i, char z)
{
	char	*s;

	s = (char*)malloc(sizeof(char) * (i + f + 1));
	if (!s)
		return (NULL);
	s[i + f] = '\0';
	i--;
	while (i + f >= f)
	{
		s[i + f] = (nb % 10) + '0';
		nb /= 10;
		i--;
	}
	if (f > 0)
		s[0] = '-';
	if (z)
		s[1] = 2 + '0';
	return (s);
}

char		*ft_itoa(int n)
{
	int		f;
	int		i;
	char	z;
	int		nb;

	f = 0;
	i = 0;
	z = 0;
	if (n == -2147483648)
	{
		n += 2000000000;
		i += 1;
		z = 1;
	}
	if (n < 0)
	{
		n *= -1;
		f += 1;
	}
	nb = n;
	i++;
	while (n /= 10)
		i++;
	return (ft_makeistr(nb, f, i, z));
}
