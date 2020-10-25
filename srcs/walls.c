/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 13:16:46 by ztawanna          #+#    #+#             */
/*   Updated: 2020/10/22 21:00:26 by ztawanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		screen_wall(t_prm *prm, int x)
{
	int color;
	int i;

	i = 0;
	get_texture(prm);
	set_wall_texture(prm);
	while (i < prm->height - 1)
	{
		if (i < prm->screen->l_end)
			if (i > prm->screen->l_start)
			{
				prm->screen->txtr_y = (int)prm->screen->txtr_pos &
												(prm->screen->txtr->h - 1);
				prm->screen->txtr_pos += prm->screen->step;
				color = prm->screen->txtr->data[prm->screen->txtr->h *
									prm->screen->txtr_y + prm->screen->txtr_x];
				*(prm->screen->data + (i * prm->width) + x) = color;
			}
			else
				*(prm->screen->data + (i * prm->width) + x) =
															prm->ceiling_color;
		else
			*(prm->screen->data + (i * prm->width) + x) = prm->floor_color;
		i++;
	}
}

void		wall_height(t_prm *prm)
{
	(prm->cam->side == 0) ? (prm->cam->wall_dist = (prm->cam->x -
	prm->player.pos_x + (1 - prm->cam->step_x) / 2) / prm->cam->ray_dir_x)
	: (prm->cam->wall_dist = (prm->cam->y - prm->player.pos_y
						+ (1 - prm->cam->step_y) / 2) / prm->cam->ray_dir_y);
	prm->screen->line_h = (int)(prm->height / prm->cam->wall_dist);
	prm->screen->l_start = -prm->screen->line_h / 2 + prm->height / 2;
	if (prm->screen->l_start < 0)
		prm->screen->l_start = 0;
	prm->screen->l_end = prm->screen->line_h / 2 + prm->height / 2;
	if (prm->screen->l_end >= prm->height)
		prm->screen->l_end = prm->height - 1;
}

void		hit_test(t_prm *prm)
{
	while (prm->cam->hit == 0)
	{
		if (prm->cam->side_x < prm->cam->side_y)
		{
			prm->cam->side_x += prm->cam->delta_x;
			prm->cam->x += prm->cam->step_x;
			prm->cam->side = 0;
		}
		else
		{
			prm->cam->side_y += prm->cam->delta_y;
			prm->cam->y += prm->cam->step_y;
			prm->cam->side = 1;
		}
		if (prm->world_map[prm->cam->x][prm->cam->y] == '1')
			prm->cam->hit = 1;
	}
}

void		calc_step_and_side(t_prm *prm)
{
	if (prm->cam->ray_dir_x < 0)
	{
		prm->cam->step_x = -1;
		prm->cam->side_x = (prm->player.pos_x - prm->cam->x)
								* prm->cam->delta_x;
	}
	else
	{
		prm->cam->step_x = 1;
		prm->cam->side_x = (prm->cam->x + 1.0 - prm->player.pos_x)
								* prm->cam->delta_x;
	}
	if (prm->cam->ray_dir_y < 0)
	{
		prm->cam->step_y = -1;
		prm->cam->side_y = (prm->player.pos_y - prm->cam->y)
								* prm->cam->delta_y;
	}
	else
	{
		prm->cam->step_y = 1;
		prm->cam->side_y = (prm->cam->y + 1.0 - prm->player.pos_y)
								* prm->cam->delta_y;
	}
}

void		wall_calculation(t_prm *prm)
{
	int x;

	x = 0;
	while (x < prm->width)
	{
		prm->cam->cam_x = 2 * x / (double)prm->width - 1;
		prm->cam->ray_dir_x = prm->player.dir_x + prm->cam->plane_x
															* prm->cam->cam_x;
		prm->cam->ray_dir_y = prm->player.dir_y + prm->cam->plane_y
															* prm->cam->cam_x;
		prm->cam->x = (int)prm->player.pos_x;
		prm->cam->y = (int)prm->player.pos_y;
		prm->cam->delta_x = fabs(1 / prm->cam->ray_dir_x);
		prm->cam->delta_y = fabs(1 / prm->cam->ray_dir_y);
		prm->cam->hit = 0;
		calc_step_and_side(prm);
		hit_test(prm);
		wall_height(prm);
		screen_wall(prm, x);
		prm->cam->z_buff[x] = prm->cam->wall_dist;
		x++;
	}
}
