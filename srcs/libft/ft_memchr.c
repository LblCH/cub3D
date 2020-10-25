/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 23:07:25 by ztawanna          #+#    #+#             */
/*   Updated: 2020/06/03 00:55:23 by ztawanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *ptr, int val, size_t n)
{
	unsigned char		c;
	unsigned char		*p;

	p = (unsigned char *)ptr;
	c = (unsigned char)val;
	while (n--)
	{
		if (*p == c)
			return ((void *)p);
		p++;
	}
	return (NULL);
}
