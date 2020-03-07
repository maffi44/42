/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validity1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjasper <bjasper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 17:29:19 by mcamila           #+#    #+#             */
/*   Updated: 2019/11/11 22:02:46 by bjasper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	ft_length(t_fill *a)
{
	int i;

	i = 0;
	a->x_len = a->sharp[i] % 10;
	a->y_len = a->sharp[i] / 10;
	++i;
	while (i < 4)
	{
		if (a->sharp[i] % 10 > a->x_len)
			a->x_len = a->sharp[i] % 10;
		if (a->sharp[i] / 10 > a->y_len)
			a->y_len = a->sharp[i] / 10;
		++i;
	}
	++a->x_len;
	++a->y_len;
}
