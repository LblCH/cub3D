/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 13:28:43 by ztawanna          #+#    #+#             */
/*   Updated: 2020/06/03 13:51:10 by ztawanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlist;
	t_list	*first;

	if (!lst)
		return (NULL);
	if (!(newlist = ft_lstnew((*f)(lst->content))))
		return (NULL);
	first = newlist;
	while (lst)
	{
		if (lst->next)
		{
			if (!(newlist->next = ft_lstnew((*f)(lst->next->content))))
			{
				ft_lstclear(&first, del);
				return (0);
			}
			newlist = newlist->next;
		}
		lst = lst->next;
	}
	newlist->next = NULL;
	return (first);
}
