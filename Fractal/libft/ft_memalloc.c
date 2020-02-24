/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 13:06:32 by mcamila           #+#    #+#             */
/*   Updated: 2019/09/15 13:12:57 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	char *p;

	p = (char*)(malloc(size));
	if (p)
	{
		while (size > 0)
		{
			p[size - 1] = '\0';
			size--;
		}
		return ((void*)p);
	}
	return (NULL);
}
