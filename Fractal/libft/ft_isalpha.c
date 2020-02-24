/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 17:12:33 by mcamila           #+#    #+#             */
/*   Updated: 2019/09/18 17:15:45 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if (c >= -128 && c <= 127)
	{
		if (((unsigned char)c >= 'a' && (unsigned char)c <= 'z') ||
			((unsigned char)c >= 'A' && (unsigned char)c <= 'Z'))
			return (1);
	}
	return (0);
}
