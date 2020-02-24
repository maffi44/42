/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 18:58:03 by mcamila           #+#    #+#             */
/*   Updated: 2019/09/11 19:06:20 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*b;
	size_t			i;
	unsigned char	d;

	b = (unsigned char*)s;
	d = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (b[i] == d)
			return ((void*)(&b[i]));
		i++;
	}
	return (NULL);
}
