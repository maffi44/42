/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 16:11:33 by mcamila           #+#    #+#             */
/*   Updated: 2019/09/16 14:23:50 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strtrim(char const *s)
{
	size_t	wcount;
	size_t	size;
	char	*ns;

	if (s)
	{
		wcount = 0;
		while (s[wcount] == '\n' || s[wcount] == '\t' || s[wcount] == ' ')
			wcount++;
		size = ft_strlen(s);
		if (wcount < size)
		{
			while (s[size - 1] == '\n' || s[size - 1] == '\t' ||
			s[size - 1] == ' ')
				size--;
			size -= wcount;
		}
		if ((ns = (char*)malloc(size + 1)) != NULL)
		{
			ns = ft_strncpy(ns, s + wcount, size);
			ns[size] = '\0';
			return (ns);
		}
	}
	return (NULL);
}
