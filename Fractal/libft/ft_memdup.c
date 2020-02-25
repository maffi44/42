/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 15:11:04 by mcamila           #+#    #+#             */
/*   Updated: 2020/02/24 19:27:52 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memdup(void const *src, size_t size)
{
	void *newsrc;

	if (src)
	{
		newsrc = (void*)ft_memalloc(sizeof(char) * size);
		if (newsrc)
		{
			newsrc = ft_memcpy(newsrc, src, size);
			return (newsrc);
		}
	}
	return (NULL);
}
