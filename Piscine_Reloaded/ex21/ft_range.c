/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 11:33:56 by mcamila           #+#    #+#             */
/*   Updated: 2019/09/09 11:48:42 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	*ft_range(int min, int max)
{
	int *range;
	int i;

	if (max > min)
	{
		range = (int *)(malloc(sizeof(int) * (max - min)));
		i = 0;
		while (min < max)
		{
			range[i] = min;
			i++;
			min++;
		}
		return (range);
	}
	return (0);
}
