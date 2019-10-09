/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 16:24:43 by mcamila           #+#    #+#             */
/*   Updated: 2019/09/19 21:01:25 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*pfrom;
	char	*pto;

	pfrom = (char*)src;
	pto = (char*)dest;
	i = 0;
	if (dest == src && n > 0)
		return (NULL);
	while (i < n)
	{
		pto[i] = pfrom[i];
		i++;
	}
	return (dest);
}
