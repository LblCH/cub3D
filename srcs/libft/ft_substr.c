/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 23:20:52 by ztawanna          #+#    #+#             */
/*   Updated: 2020/06/03 13:15:22 by ztawanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	i;
	size_t	size;

	i = 0;
	if (!s || start > ft_strlen(s) || len == 0 || ft_strlen(s) == 0
		|| (ft_strlen(s) - start) <= 0)
		return (ft_strdup(""));
	size = ft_strlen(s) - start;
	if (size < len)
		len = size;
	if (!(res = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (s[start + i] && i < len)
	{
		res[i] = s[start + i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
