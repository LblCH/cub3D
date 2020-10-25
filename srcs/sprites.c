/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 15:15:15 by ztawanna          #+#    #+#             */
/*   Updated: 2020/10/22 23:12:45 by ztawanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		draw_sprite(t_prm *prm, int stripe)
{
	int	y;
	int	d;
	int	color;

	y = prm->sprite->start_y;
	prm->sprite->txtr_x = (int)(256 * (stripe - (-prm->sprite->width / 2 +
		prm->sprite->screen_x)) * prm->txtr_spr->w / prm->sprite->width) / 256;
	if (prm->sprite->trnfm_y > 0 && stripe > 0 && stripe < prm->width &&
			prm->sprite->trnfm_y < prm->cam->z_buff[stripe])
		while (y < prm->sprite->end_y)
		{
			d = (y - prm->sprite->vms) * 256 - prm->height * 128
													+ prm->sprite->height * 128;
			prm->sprite->txtr_y = ((d * prm->txtr_spr->h) /
													prm->sprite->height) / 256;
			color = prm->txtr_spr->data[prm->txtr_spr->w * prm->sprite->txtr_y +
													prm->sprite->txtr_x];
			if (color != prm->txtr_spr->data[0])
				*(prm->screen->data + (y * prm->width) + stripe) = color;
			y++;
		}
}

void		get_sprite_height_draw(t_prm *prm)
{
	int	stripe;

	prm->sprite->screen_x = (int)((prm->width / 2) * (1 + prm->sprite->trnfm_x /
												prm->sprite->trnfm_y));
	prm->sprite->vms = (int)((prm->height / 4) / prm->sprite->trnfm_y);
	prm->sprite->height = abs((int)(prm->height / prm->sprite->trnfm_y));
	prm->sprite->start_y = -prm->sprite->height / 2 + prm->height / 2
												+ prm->sprite->vms;
	if (prm->sprite->start_y < 0)
		prm->sprite->start_y = 0;
	prm->sprite->end_y = prm->sprite->height / 2 + prm->height / 2
												+ prm->sprite->vms;
	if (prm->sprite->end_y >= prm->height)
		prm->sprite->end_y = prm->height - 1;
	prm->sprite->width = abs((int)(prm->height / prm->sprite->trnfm_y));
	prm->sprite->start_x = -prm->sprite->width / 2 + prm->sprite->screen_x;
	if (prm->sprite->start_x < 0)
		prm->sprite->start_x = 0;
	prm->sprite->end_x = prm->sprite->width / 2 + prm->sprite->screen_x;
	if (prm->sprite->end_x >= prm->width)
		prm->sprite->end_x = prm->width - 1;
	stripe = prm->sprite->start_x;
	while (stripe < prm->sprite->end_x)
		draw_sprite(prm, stripe++);
}

int			get_active_spr_index(t_prm *prm)
{
	int i;
	int act_i;

	i = 0;
	act_i = 0;
	while (i < prm->sprite->num && prm->sprite->used[i] != 0)
		i++;
	act_i = i;
	i = 0;
	while (i < prm->sprite->num)
	{
		if (prm->sprite->distance[act_i] < prm->sprite->distance[i] &&
											prm->sprite->used[i] == 0)
			act_i = i;
		i++;
	}
	prm->sprite->used[act_i] = 1;
	return (act_i);
}

void		get_sprites_coord(t_prm *prm)
{
	int i;
	int x;
	int y;

	x = 0;
	i = 0;
	while (x < prm->map_width)
	{
		y = 0;
		while (y < prm->map_height)
		{
			if (prm->world_map[x][y] == '2')
			{
				prm->sprite->x[i] = x + 0.6;
				prm->sprite->y[i] = y + 0.6;
				i++;
			}
			y++;
		}
		x++;
	}
}

void		sprites_casting(t_prm *prm)
{
	int i;
	int act_i;

	i = 0;
	while (i < prm->sprite->num)
	{
		prm->sprite->distance[i] = pow((prm->player.pos_x - prm->sprite->x[i]),
			2) + pow((prm->player.pos_y - prm->sprite->y[i]), 2);
		prm->sprite->used[i++] = 0;
	}
	i = 0;
	while (i < prm->sprite->num)
	{
		act_i = get_active_spr_index(prm);
		prm->sprite->pos_x = prm->sprite->x[act_i] - prm->player.pos_x;
		prm->sprite->pos_y = prm->sprite->y[act_i] - prm->player.pos_y;
		prm->inv_det = 1.0 / (prm->cam->plane_x * prm->player.dir_y
								- prm->player.dir_x * prm->cam->plane_y);
		prm->sprite->trnfm_x = prm->inv_det * (prm->player.dir_y *
			prm->sprite->pos_x - prm->player.dir_x * prm->sprite->pos_y);
		prm->sprite->trnfm_y = prm->inv_det * (-prm->cam->plane_y *
			prm->sprite->pos_x + prm->cam->plane_x * prm->sprite->pos_y);
		get_sprite_height_draw(prm);
		i++;
	}
}
