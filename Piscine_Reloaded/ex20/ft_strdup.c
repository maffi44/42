/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 20:11:30 by mcamila           #+#    #+#             */
/*   Updated: 2019/09/09 10:50:31 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strdup(char *src)
{
	int		i;
	char	*new_str;

	if (src)
	{
		i = 0;
		while (src[i] != '\0')
		{
			i++;
		}
		new_str = (char *)(malloc(sizeof(char) * i));
		i = 0;
		while (src[i] != '\0')
		{
			new_str[i] = src[i];
			i++;
		}
		new_str[i] = '\0';
		return (new_str);
	}
	return (0);
}
