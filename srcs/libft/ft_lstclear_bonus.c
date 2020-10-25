/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 22:47:57 by ztawanna          #+#    #+#             */
/*   Updated: 2020/06/01 22:52:04 by ztawanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;
	t_list	*nxt;

	tmp = *lst;
	nxt = NULL;
	while (tmp)
	{
		nxt = tmp->next;
		(*del)(tmp->content);
		free(tmp);
		tmp = nxt;
	}
	*lst = NULL;
}
