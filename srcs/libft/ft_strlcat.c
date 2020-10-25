/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 23:09:51 by ztawanna          #+#    #+#             */
/*   Updated: 2020/06/01 20:02:00 by ztawanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t		n;
	size_t		l;
	char		*d;
	char		*s;

	d = dst;
	s = (char *)src;
	n = size;
	while (*d != '\0' && n-- != 0)
		d++;
	l = d - dst;
	n = size - l;
	if (n <= 0)
		return (l + ft_strlen(src));
	while (*s != '\0')
	{
		if (n > 1)
		{
			*d++ = *s;
			n--;
		}
		s++;
	}
	*d = '\0';
	return (l + (s - src));
}
