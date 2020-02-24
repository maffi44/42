/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 14:42:30 by mcamila           #+#    #+#             */
/*   Updated: 2019/09/20 19:14:59 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char	**ft_freenewlist(char **new_list, size_t count)
{
	while (new_list[count])
	{
		free(new_list[count]);
		count++;
	}
	free(new_list);
	return (NULL);
}

static char	**ft_makesstr(const char *s, size_t count, size_t i, char **nlst)
{
	if (i != 0)
		nlst[count] = (char *)malloc(sizeof(char) * (i + 1));
	else
	{
		nlst[count] = NULL;
		return (nlst);
	}
	if (nlst[count])
	{
		nlst[count][i] = '\0';
		while (i > 0)
		{
			(nlst[count])[i - 1] = s[i - 1];
			i--;
		}
	}
	else
		nlst = ft_freenewlist(nlst, count);
	return (nlst);
}

static char	**ft_recstrsplit(const char *s, char c, size_t count, char **nlst)
{
	size_t i;
	size_t j;

	i = 0;
	while (s[i] != '\0' && s[i] != c)
		i++;
	j = i;
	while (s[j] == c)
		j++;
	if (s[j] != '\0')
		nlst = ft_recstrsplit(&(s[j]), c, count + 1, nlst);
	else
	{
		nlst = (char**)malloc(sizeof(char*) * (count + 2));
		if (nlst)
			nlst[count + 1] = NULL;
	}
	if (nlst)
	{
		return (ft_makesstr(s, count, i, nlst));
	}
	return (NULL);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**slist;

	if (s)
	{
		while (*s == c)
			s++;
		slist = NULL;
		return (ft_recstrsplit((char*)s, c, 0, slist));
	}
	return (NULL);
}
