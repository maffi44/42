/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 15:46:04 by mcamila           #+#    #+#             */
/*   Updated: 2019/09/15 15:56:21 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ns;

	if (s1 && s2)
	{
		ns = (char*)(malloc(ft_strlen(s1) + ft_strlen(s2) + 1));
		if (ns)
		{
			ft_strcpy(ns, s1);
			ft_strcat(ns, s2);
			return (ns);
		}
	}
	if (s1 && !s2)
		return (ft_strdup(s1));
	if (s2 && !s1)
		return (ft_strdup(s2));
	return (NULL);
}
