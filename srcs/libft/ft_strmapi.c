/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 23:36:25 by ztawanna          #+#    #+#             */
/*   Updated: 2020/05/30 23:38:28 by ztawanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	size_t	len;
	char	*str;

	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	if (!(str = malloc(sizeof(char) * len + 1)))
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = (*f)(i, (char)s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
