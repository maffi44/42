/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 14:12:14 by mcamila           #+#    #+#             */
/*   Updated: 2020/02/24 19:27:52 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmap(char const *s, char (*f)(char))
{
	size_t	i;
	char	*ns;

	if (!s || !f)
		return (NULL);
	i = ft_strlen(s);
	ns = (char*)(malloc(i + 1));
	if (ns)
	{
		ns[i] = '\0';
		while (i > 0)
		{
			ns[i - 1] = f(s[i - 1]);
			i--;
		}
		return (ns);
	}
	return (NULL);
}
