/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_set.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 17:54:16 by ztawanna          #+#    #+#             */
/*   Updated: 2020/10/25 18:35:26 by ztawanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		check_map(t_prm *prm)
{
	int i;
	int j;

	i = 0;
	while (i < prm->map_width)
	{
		j = 0;
		while (j < prm->map_height)
		{
			if (prm->world_map[i][j] == ' ' && ((i != 0 &&
				prm->world_map[i - 1][j] == '0') || (i != 0 &&
				prm->world_map[i - 1][j] == '2') || (j != 0 &&
				prm->world_map[i][j - 1] == '0') || (j != 0 &&
				prm->world_map[i][j - 1] == '2')))
				error_handler(BAD_MAP_ERR);
			if ((prm->world_map[i][j] == '0' || prm->world_map[i][j] == '2') &&
				(i == 0 || j == 0 || i == prm->map_width - 1 ||
				j == prm->map_height - 1 || prm->world_map[i - 1][j] == ' ' ||
				prm->world_map[i][j - 1] == ' '))
				error_handler(BAD_MAP_ERR);
			j++;
		}
		i++;
	}
	if (prm->player.dir == '0')
		error_handler(BAD_MAP_ERR);
}

void		check_and_set_pos(t_prm *prm, int i, int j, int z)
{
	if (prm->map_str[z] == '0' || prm->map_str[z] == '1' ||
														prm->map_str[z] == ' ')
		prm->world_map[i][j] = prm->map_str[z];
	else if (prm->map_str[z] == '2')
	{
		prm->sprite->num++;
		prm->world_map[i][j] = prm->map_str[z];
	}
	else if ((prm->map_str[z] == 'N' || prm->map_str[z] == 'S' ||
		prm->map_str[z] == 'W' || prm->map_str[z] == 'E') &&
														prm->player.dir == '0')
	{
		prm->player.pos_x = i + 0.5;
		prm->player.pos_y = j + 0.5;
		prm->player.dir = prm->map_str[z];
		prm->world_map[i][j] = '0';
	}
	else
		error_handler(BAD_MAP_ERR);
}

void		check_params(t_prm *prm)
{
	int i;

	i = 0;
	if (*prm->txtr_n->data == 0 || *prm->txtr_s->data == 0
		|| *prm->txtr_w->data == 0 || *prm->txtr_e->data == 0
		|| *prm->txtr_spr->data == 0)
		error_handler(TEXTURE_ERR);
	if (prm->width == 0 || prm->height == 0)
		error_handler(RESOL_ERR);
	if (prm->floor_color == -1 || prm->ceiling_color == -1)
		error_handler(COLOR_ERR);
	if (prm->map_width < 3 && prm->map_height < 3)
		error_handler(BAD_MAP_ERR);
	if (!(prm->world_map = (char**)malloc(prm->map_width * sizeof(char*))))
		error_handler(MALLOC_ERR);
	while (i < prm->map_width)
		if (!(prm->world_map[i++] = (char*)malloc(prm->map_height *
															sizeof(char))))
			error_handler(MALLOC_ERR);
}

void		check_and_set_map(t_prm *prm)
{
	int i;
	int j;
	int z;

	z = 0;
	check_params(prm);
	j = 0;
	while (j < prm->map_height)
	{
		i = 0;
		while (prm->map_str[z] != '\n')
		{
			check_and_set_pos(prm, i++, j, z);
			z++;
		}
		while (i < prm->map_width)
			prm->world_map[i++][j] = ' ';
		z++;
		j++;
	}
	free(prm->map_str);
	check_map(prm);
}
