/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 14:22:28 by mcamila           #+#    #+#             */
/*   Updated: 2019/09/15 14:34:11 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*ns;
	size_t	i;

	if (!s || !f)
		return (NULL);
	i = ft_strlen(s);
	ns = (char*)(malloc(i + 1));
	if (ns)
	{
		ns[i] = '\0';
		while (i > 0)
		{
			ns[i - 1] = f(i - 1, s[i - 1]);
			i--;
		}
		return (ns);
	}
	return (NULL);
}
