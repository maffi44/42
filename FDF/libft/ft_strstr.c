/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 16:38:33 by mcamila           #+#    #+#             */
/*   Updated: 2019/09/19 15:30:12 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *lit)
{
	int i;
	int j;

	if (lit[0] == '\0')
		return ((char*)big);
	i = 0;
	while (big[i] != '\0')
	{
		j = 0;
		while (big[i + j] == lit[j] && big[i + j] != '\0')
		{
			if (lit[j + 1] == '\0')
				return ((char*)(&big[i]));
			if (big[i + j + 1] == '\0')
				return (NULL);
			j++;
		}
		i++;
	}
	return (NULL);
}
