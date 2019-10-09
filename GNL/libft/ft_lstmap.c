/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 16:04:11 by mcamila           #+#    #+#             */
/*   Updated: 2019/09/21 17:35:49 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static t_list	*ft_lstfree(t_list *lst)
{
	if (!lst)
		return (NULL);
	ft_lstfree(lst->next);
	free(lst->content);
	free(lst);
	return (NULL);
}

t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*newlst;
	t_list	*first;

	if (!lst || !f)
		return (NULL);
	if (!(newlst = f(lst)))
		return (NULL);
	first = newlst;
	while (lst->next)
	{
		if (!(newlst->next = f(lst->next)))
			return (ft_lstfree(first));
		newlst = newlst->next;
		lst = lst->next;
	}
	return (first);
}
