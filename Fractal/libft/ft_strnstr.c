/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 17:01:55 by mcamila           #+#    #+#             */
/*   Updated: 2019/09/14 17:12:25 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t i;
	size_t j;

	if (little[0] == '\0')
		return ((char*)big);
	i = 0;
	while (big[i] != '\0' && i < len)
	{
		j = 0;
		while (big[i + j] == little[j] && big[i + j] != '\0' && i + j < len)
		{
			if (little[j + 1] == '\0')
				return ((char*)(&big[i]));
			if (big[i + j + 1] == '\0')
				return (NULL);
			j++;
		}
		i++;
	}
	return (NULL);
}
