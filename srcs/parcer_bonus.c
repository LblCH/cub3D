/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 03:51:38 by ztawanna          #+#    #+#             */
/*   Updated: 2020/10/29 02:37:56 by ztawanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void		init_map(char *line, t_prm *prm)
{
	char	*temp;
	char	*temp2;
	size_t	len;

	len = ft_strlen(line);
	prm->map_width = ((int)len > prm->map_width) ? len : prm->map_width;
	if (len < 1)
		error_handler(BAD_MAP_ERR);
	temp = ft_strjoin(prm->map_str, line);
	temp2 = ft_strjoin(temp, "\n");
	free(prm->map_str);
	free(temp);
	prm->map_str = temp2;
	prm->map_height++;
}

void		init_resolution(char *line, t_prm *prm)
{
	int		i;
	int		screen_width;
	int		screen_height;

	i = 1;
	if (prm->width > 0)
		error_handler(RESOL_ERR);
	mlx_get_screen_size(prm->mlx_ptr, &screen_width, &screen_height);
	while (ft_isspace(line[i]))
		i++;
	if ((prm->width = ft_atoi(&line[i])) > screen_width || prm->width == -1)
		prm->width = screen_width;
	while (ft_isdigit(line[i]))
		i++;
	while (ft_isspace(line[i]))
		i++;
	if ((prm->height = ft_atoi(&line[i])) > screen_height || prm->height == -1)
		prm->height = screen_height;
	while (ft_isdigit(line[i]))
		i++;
	while (ft_isspace(line[i]))
		i++;
	if (prm->width < 1 || prm->height < 1)
		error_handler(RESOL_ERR);
}

void		init_floor_n_ceiling(char *line, t_prm *prm, int i)
{
	int		x;
	int		color;
	int		rgb;

	x = 2;
	while (ft_isspace(line[i]))
		i++;
	while (line[i])
	{
		(ft_isdigit(line[i]) && x != -1) ? color = ft_atoi(&line[i]) :
													error_handler(COLOR_ERR);
		if (color < 0 || color > 255)
			error_handler(COLOR_ERR);
		rgb = (rgb | (color << (8 * (x--))));
		while (ft_isdigit(line[i]))
			i++;
		while (ft_isspace(line[i]))
			i++;
		if (line[i])
			((line[i] == ',' || x == -1) && !ft_isdigit(line[i])) ? i++ :
													error_handler(COLOR_ERR);
		while (ft_isspace(line[i]))
			i++;
	}
	init_floor_n_ceiling2(line[0], prm, x, rgb);
}

void		init_floor_n_ceiling2(char c, t_prm *prm, int x, int rgb)
{
	if (x != -1)
		error_handler(COLOR_ERR);
	else if (c == 'F' && prm->floor_color == -1)
		(prm->floor_color = rgb);
	else if (c == 'C' && prm->ceiling_color == -1)
		(prm->ceiling_color = rgb);
	else
		error_handler(COLOR_ERR);
}

void		parcing(int fd, t_prm *prm)
{
	char	*line;
	int		i;
	int		map_flag;

	i = 0;
	while (get_next_line(fd, &line) > 0)
	{
		if (line[i] && line[i] == 'R' && line[i + 1] == ' ')
			init_resolution(line, prm);
		else if (line[i] && ft_strchr("NSWE", line[i]))
			set_texture(line, prm);
		else if (line[i] && ft_strchr("FC", line[i]) && line[i + 1] == ' ')
			init_floor_n_ceiling(line, prm, 1);
		else if (line[i] && line[i] == 'F' && line[i + 1] == 'L')
			set_texture(line, prm);
		else if (line[i] == '1' || line[i] == ' ')
		{
			map_flag = 1;
			init_map(line, prm);
		}
		else if (line[i] != '\0' || map_flag == 1)
			error_handler(MAP_FILE_ERR);
		free(line);
	}
	free(line);
}
