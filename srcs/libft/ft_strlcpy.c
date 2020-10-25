/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 23:09:23 by ztawanna          #+#    #+#             */
/*   Updated: 2020/05/30 22:42:58 by ztawanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	n;
	size_t	len;

	if (!dst || !src)
		return (0);
	n = ft_strlen(src);
	if (size)
	{
		if (n >= size)
			len = size - 1;
		else
			len = n;
		ft_memcpy(dst, src, len);
		dst[len] = '\0';
	}
	return (n);
}
