/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 23:23:04 by ztawanna          #+#    #+#             */
/*   Updated: 2020/08/02 19:20:15 by ztawanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		find_index(const char *s, int c)
{
	int		i;

	i = 0;
	while (s[i] && s[i] != (char)c)
		i++;
	if (s[i] != (char)c)
		return (-1);
	return (i);
}

int		get_line(char *str, char **line, int i)
{
	*line = ft_substr(str, 0, i);
	++i;
	ft_memmove(str, str + i, (ft_strlen(str + i) + 1));
	return (1);
}

int		get_next_line(int fd, char **line)
{
	char			buff[BUFFER_SIZE + 1];
	static char		*str = NULL;
	int				res;
	int				i;

	if (!line || fd < 0 || BUFFER_SIZE < 1 || read(fd, buff, 0) < 0)
		return (-1);
	if (str && (((i = find_index(str, '\n')) != -1)))
		return (get_line(str, line, i));
	while (((res = read(fd, buff, BUFFER_SIZE)) > 0))
	{
		buff[res] = '\0';
		str = add_and_free(str, buff);
		if (((i = find_index(str, '\n')) != -1))
			return (get_line(str, line, i));
	}
	if (str)
	{
		*line = ft_strdup(str);
		free(str);
		str = NULL;
		return (res);
	}
	*line = ft_strdup("");
	return (res);
}
