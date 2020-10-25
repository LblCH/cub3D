/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 23:11:21 by ztawanna          #+#    #+#             */
/*   Updated: 2020/05/30 11:14:20 by ztawanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (ft_strlen(big) < ft_strlen(little) || len < ft_strlen(little))
		return (NULL);
	if (little[0] == '\0')
		return ((char *)big);
	while (big[i] && i + j < len)
	{
		if (big[i + j] == little[j])
		{
			if (little[++j] == '\0')
				return ((char *)big + i);
		}
		else
		{
			j = 0;
			i++;
		}
	}
	return (NULL);
}
