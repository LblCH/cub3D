/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 23:21:54 by ztawanna          #+#    #+#             */
/*   Updated: 2020/06/03 13:21:53 by ztawanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	word_len(char const *w, char c)
{
	size_t	i;

	i = 0;
	while (w[i] != c && w[i] != '\0')
		i++;
	return (i);
}

static size_t	count_words(char const *s, char c)
{
	size_t	cnt;
	size_t	cnted;

	cnt = 0;
	cnted = 0;
	while (*s != '\0')
	{
		if (cnted == 0 && *s != c)
		{
			cnt++;
			cnted = 1;
		}
		else if (cnted == 1 && *s == c)
			cnted = 0;
		s++;
	}
	return (cnt);
}

static char		*copy_word(char const *s, char c)
{
	size_t	i;
	char	*word;

	if (!(word = malloc(sizeof(char) * (word_len(s, c) + 1))))
		return (NULL);
	i = 0;
	while (*s != c && *s != '\0')
		word[i++] = *s++;
	word[i] = '\0';
	return (word);
}

static void		ft_freetab(char **str, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char			**ft_split(char const *s, char c)
{
	char	**res;
	size_t	i;

	i = 0;
	if (!(s) || !(res = malloc(sizeof(char *) * (count_words(s, c) + 1))))
		return (NULL);
	while (*s != '\0')
	{
		if (*s == c)
			s++;
		if (*s != c && *s != '\0')
		{
			if (!(res[i++] = copy_word(s, c)))
			{
				ft_freetab(res, count_words(s, c));
				return (NULL);
			}
			s += word_len(s, c);
		}
	}
	res[i] = NULL;
	return (res);
}
