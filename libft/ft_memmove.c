/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 18:43:59 by mcamila           #+#    #+#             */
/*   Updated: 2019/09/20 15:58:35 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*pto;
	const unsigned char	*pfrom;

	if (!dest && !src)
		return (NULL);
	pfrom = (const unsigned char*)src;
	pto = (unsigned char*)dest;
	if (pfrom > pto)
		ft_memcpy(dest, src, n);
	else
	{
		while (n > 0)
		{
			pto[n - 1] = pfrom[n - 1];
			n--;
		}
	}
	return (dest);
}
