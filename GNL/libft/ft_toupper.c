/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 17:42:27 by mcamila           #+#    #+#             */
/*   Updated: 2019/10/12 21:38:09 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_islower(char c)
{
	if (c >= -128 && c <= 127)
	{
		if ((unsigned char)c >= 'a' && (unsigned char)c <= 'z')
			return (1);
	}
	return (0);
}

int			ft_toupper(int c)
{
	if (c >= -128 && c <= 127)
	{
		if (ft_islower(c))
			return (c - 32);
	}
	return (c);
}
