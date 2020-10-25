/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 23:21:21 by ztawanna          #+#    #+#             */
/*   Updated: 2020/05/31 00:11:45 by ztawanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	is_set(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	char const	*s;
	char		*res;
	size_t		i;

	if (!(s1))
		return (NULL);
	s = s1;
	while (*s != '\0')
		s++;
	while (is_set(*s, set) || *s == '\0')
		s--;
	while (is_set(*s1, set))
		s1++;
	if (s < s1)
		return (ft_calloc(1, sizeof(char)));
	if (!(res = malloc(sizeof(char) * ((s - s1) + 2))))
		return (NULL);
	i = 0;
	while (s1 <= s)
		res[i++] = *s1++;
	res[i] = '\0';
	return (res);
}
