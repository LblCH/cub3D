/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys2_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 11:00:55 by ztawanna          #+#    #+#             */
/*   Updated: 2020/10/29 02:38:08 by ztawanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void		move_left(t_prm *prm)
{
	if (prm->world_map[(int)(prm->player.pos_x - prm->cam->plane_x *
			prm->player.mv_spd)][(int)(prm->player.pos_y)] == '0' ||
			prm->world_map[(int)(prm->player.pos_x - prm->cam->plane_x *
			prm->player.mv_spd)][(int)(prm->player.pos_y)] == 'T')
		prm->player.pos_x -= prm->cam->plane_x * prm->player.mv_spd;
	if (prm->world_map[(int)(prm->player.pos_x)][(int)(prm->player.pos_y -
			prm->cam->plane_y * prm->player.mv_spd)] == '0' ||
			prm->world_map[(int)(prm->player.pos_x)][(int)(prm->player.pos_y -
			prm->cam->plane_y * prm->player.mv_spd)] == 'T')
		prm->player.pos_y -= prm->cam->plane_y * prm->player.mv_spd;
}

void		move_right(t_prm *prm, int key)
{
	if (key == KEY_D)
	{
		if (prm->world_map[(int)(prm->player.pos_x + prm->cam->plane_x *
			prm->player.mv_spd)][(int)(prm->player.pos_y)] == '0' ||
			prm->world_map[(int)(prm->player.pos_x + prm->cam->plane_x *
				prm->player.mv_spd)][(int)(prm->player.pos_y)] == 'T')
			prm->player.pos_x += prm->cam->plane_x * prm->player.mv_spd;
		if (prm->world_map[(int)(prm->player.pos_x)][(int)(prm->player.pos_y +
			prm->cam->plane_y * prm->player.mv_spd)] == '0' ||
			prm->world_map[(int)(prm->player.pos_x)][(int)(prm->player.pos_y +
				prm->cam->plane_y * prm->player.mv_spd)] == 'T')
			prm->player.pos_y += prm->cam->plane_y * prm->player.mv_spd;
	}
	if (key == KEY_A)
		move_left(prm);
}

void		move_down(t_prm *prm)
{
	if (prm->world_map[(int)(prm->player.pos_x - prm->player.dir_x *
		prm->player.mv_spd)][(int)(prm->player.pos_y)] == '0' ||
		prm->world_map[(int)(prm->player.pos_x - prm->player.dir_x *
			prm->player.mv_spd)][(int)(prm->player.pos_y)] == 'T')
		prm->player.pos_x -= prm->player.dir_x * prm->player.mv_spd;
	if (prm->world_map[(int)(prm->player.pos_x)][(int)(prm->player.pos_y -
		prm->player.dir_y * prm->player.mv_spd)] == '0' ||
		prm->world_map[(int)(prm->player.pos_x)][(int)(prm->player.pos_y -
			prm->player.dir_y * prm->player.mv_spd)] == 'T')
		prm->player.pos_y -= prm->player.dir_y * prm->player.mv_spd;
}

void		move_up(t_prm *prm, int key)
{
	if (key == KEY_W)
	{
		if (prm->world_map[(int)(prm->player.pos_x + prm->player.dir_x *
			prm->player.mv_spd)][(int)(prm->player.pos_y)] == '0' ||
			prm->world_map[(int)(prm->player.pos_x + prm->player.dir_x *
				prm->player.mv_spd)][(int)(prm->player.pos_y)] == 'T')
			prm->player.pos_x += prm->player.dir_x * prm->player.mv_spd;
		if (prm->world_map[(int)(prm->player.pos_x)][(int)(prm->player.pos_y +
			prm->player.dir_y * prm->player.mv_spd)] == '0' ||
			prm->world_map[(int)(prm->player.pos_x)][(int)(prm->player.pos_y +
				prm->player.dir_y * prm->player.mv_spd)] == 'T')
			prm->player.pos_y += prm->player.dir_y * prm->player.mv_spd;
	}
	if (key == KEY_S)
		move_down(prm);
}

void		look_up_down_jump_crouch(t_prm *prm, int key)
{
	if (key == KEY_UP)
	{
		prm->player.pitch += (prm->height * 1 / 2) * prm->player.mv_spd;
		if (prm->player.pitch > prm->height / 4)
			prm->player.pitch = prm->height / 4;
	}
	if (key == KEY_DOWN)
	{
		prm->player.pitch -= (prm->height * 2 / 3) * prm->player.mv_spd;
		if (prm->player.pitch < -prm->height / 3)
			prm->player.pitch = -prm->height / 3;
	}
	if (key == KEY_SPACE)
	{
		prm->player.pos_z = prm->height / 3;
	}
	if (key == KEY_C)
	{
		prm->player.pos_z = -prm->height / 3;
	}
}
