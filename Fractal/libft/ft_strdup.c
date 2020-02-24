/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 19:43:44 by mcamila           #+#    #+#             */
/*   Updated: 2019/09/11 20:00:34 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*s2;

	i = 0;
	while (s1[i] != '\0')
		i++;
	s2 = (char*)(malloc(sizeof(char) * (i + 1)));
	if (s2)
	{
		i = 0;
		while (s1[i] != '\0')
		{
			s2[i] = s1[i];
			i++;
		}
		s2[i] = '\0';
	}
	return (s2);
}
