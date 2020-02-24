/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 13:27:48 by mcamila           #+#    #+#             */
/*   Updated: 2019/09/21 14:59:11 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void*, size_t))
{
	if (!alst || !del)
		return ;
	if ((*alst)->next)
		ft_lstdel(&((*alst)->next), del);
	ft_lstdelone(alst, del);
}
