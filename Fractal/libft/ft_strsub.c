/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 15:32:32 by mcamila           #+#    #+#             */
/*   Updated: 2019/09/15 15:43:46 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*ns;
	size_t	i;

	if (s)
	{
		ns = (char*)(malloc(len + 1));
		if (ns)
		{
			i = 0;
			ns[len] = '\0';
			while (i < len)
			{
				ns[i] = s[start];
				start++;
				i++;
			}
			return (ns);
		}
	}
	return (NULL);
}
