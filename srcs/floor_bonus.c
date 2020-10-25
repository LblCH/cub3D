/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 20:21:42 by ztawanna          #+#    #+#             */
/*   Updated: 2020/10/24 20:30:30 by ztawanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int			get_sprite_pixel(t_prm *prm, int i, int d, int stripe)
{
	if (prm->world_map[(int)(prm->sprite->x[i] - 0.6)][(int)(prm->sprite->y[i]
		- 0.6)] == '2')
	{
		return (prm->txtr_spr->data[prm->txtr_spr->w * prm->sprite->txtr_y +
												prm->sprite->txtr_x]);
	}
	if (prm->world_map[(int)(prm->sprite->x[i] - 0.6)][(int)(prm->sprite->y[i]
		- 0.6)] == '3')
	{
		prm->sprite->txtr_x = (int)(256 * (stripe - (-prm->sprite->width / 2 +
			prm->sprite->screen_x)) * prm->txtr_spr->w2 / prm->sprite->width)
			/ 256;
		prm->sprite->txtr_y = ((d * prm->txtr_spr->h2) /
													prm->sprite->height) / 256;
		return (prm->txtr_spr->data2[(prm->txtr_spr->w2) * prm->sprite->txtr_y +
			prm->sprite->txtr_x / 4 + prm->tick * (prm->txtr_spr->w2 / 4)]);
	}
	return (0);
}

void		draw_floor(t_prm *prm, int y, int x)
{
	int cell_x;
	int cell_y;
	int tx;
	int ty;
	int color;

	while (x < prm->width)
	{
		cell_x = (int)(prm->cam->fl_x);
		cell_y = (int)(prm->cam->fl_y);
		tx = (int)(prm->txtr_fl->w * (prm->cam->fl_x - cell_x)) &
				(prm->txtr_fl->w - 1);
		ty = (int)(prm->txtr_fl->h * (prm->cam->fl_y - cell_y)) &
				(prm->txtr_fl->h - 1);
		color = prm->txtr_fl->data[prm->txtr_fl->w * ty + tx];
		*(prm->screen->data + (y * prm->width) + x) = color;
		prm->cam->fl_x += prm->cam->fl_st_x;
		prm->cam->fl_y += prm->cam->fl_st_y;
		++x;
	}
}

void		floor_raycasting(t_prm *prm)
{
	int		p;
	int		x;
	int		y;
	float	row_dist;

	y = 0;
	while (y < prm->height)
	{
		prm->cam->ray_dir_x0 = prm->player.dir_x - prm->cam->plane_x;
		prm->cam->ray_dir_y0 = prm->player.dir_y - prm->cam->plane_y;
		prm->cam->ray_dir_x1 = prm->player.dir_x + prm->cam->plane_x;
		prm->cam->ray_dir_y1 = prm->player.dir_y + prm->cam->plane_y;
		p = y - prm->height / 2 - prm->player.pitch;
		prm->cam->pos_z = 0.5 * prm->height + prm->player.pos_z;
		row_dist = prm->cam->pos_z / p;
		prm->cam->fl_st_x = row_dist * (prm->cam->ray_dir_x1 -
										prm->cam->ray_dir_x0) / prm->width;
		prm->cam->fl_st_y = row_dist * (prm->cam->ray_dir_y1 -
										prm->cam->ray_dir_y0) / prm->width;
		prm->cam->fl_x = prm->player.pos_x + row_dist * prm->cam->ray_dir_x0;
		prm->cam->fl_y = prm->player.pos_y + row_dist * prm->cam->ray_dir_y0;
		x = 0;
		draw_floor(prm, y, x);
		y++;
	}
}
