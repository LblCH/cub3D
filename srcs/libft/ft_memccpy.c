/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 23:02:42 by ztawanna          #+#    #+#             */
/*   Updated: 2020/05/29 23:56:33 by ztawanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*srctmp;
	unsigned char	*dsttmp;

	i = 0;
	srctmp = (unsigned char *)src;
	dsttmp = (unsigned char *)dst;
	while (n--)
	{
		dsttmp[i] = srctmp[i];
		if (srctmp[i] == (unsigned char)c)
			return (dsttmp + i + 1);
		i++;
	}
	return (NULL);
}
