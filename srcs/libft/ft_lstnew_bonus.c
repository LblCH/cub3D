/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 22:21:24 by ztawanna          #+#    #+#             */
/*   Updated: 2020/06/01 22:40:00 by ztawanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	struct s_list *res;

	if (!(res = malloc(sizeof(struct s_list))))
		return (NULL);
	res[0].content = content;
	res[0].next = NULL;
	return (res);
}
