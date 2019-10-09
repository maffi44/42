/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 16:46:23 by mcamila           #+#    #+#             */
/*   Updated: 2019/09/18 18:03:35 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t	i;
	char	*pfrom;
	char	*pto;

	pfrom = (char*)src;
	pto = (char*)dest;
	i = 0;
	while (i < n)
	{
		if (pfrom[i] != (char)c)
		{
			pto[i] = pfrom[i];
			i++;
		}
		else
		{
			pto[i] = pfrom[i];
			return ((void*)&pto[i + 1]);
		}
	}
	return (NULL);
}
