/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 01:11:26 by ztawanna          #+#    #+#             */
/*   Updated: 2020/10/28 05:55:27 by ztawanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			ft_exit(t_prm *prm)
{
	int i;

	i = 0;
	free(prm->cam->z_buff);
	free(prm->txtr_n);
	free(prm->txtr_s);
	free(prm->txtr_w);
	free(prm->txtr_e);
	free(prm->txtr_spr);
	free(prm->screen);
	free(prm->cam);
	free(prm->sprite->used);
	free(prm->sprite->distance);
	free(prm->sprite->x);
	free(prm->sprite->y);
	free(prm->sprite);
	while (i < prm->map_width)
		free(prm->world_map[i++]);
	free(prm->world_map);
	mlx_destroy_window(prm->mlx_ptr, prm->win_ptr);
	exit(0);
}

void		move_left_right(t_prm *prm, int key)
{
	if (key == KEY_D)
	{
		if (prm->world_map[(int)(prm->player.pos_x + prm->cam->plane_x *
			prm->player.mv_spd)][(int)(prm->player.pos_y)] != '1')
			prm->player.pos_x += prm->cam->plane_x * prm->player.mv_spd;
		if (prm->world_map[(int)(prm->player.pos_x)][(int)(prm->player.pos_y +
			prm->cam->plane_y * prm->player.mv_spd)] != '1')
			prm->player.pos_y += prm->cam->plane_y * prm->player.mv_spd;
	}
	if (key == KEY_A)
	{
		if (prm->world_map[(int)(prm->player.pos_x - prm->cam->plane_x *
			prm->player.mv_spd)][(int)(prm->player.pos_y)] != '1')
			prm->player.pos_x -= prm->cam->plane_x * prm->player.mv_spd;
		if (prm->world_map[(int)(prm->player.pos_x)][(int)(prm->player.pos_y -
			prm->cam->plane_y * prm->player.mv_spd)] != '1')
			prm->player.pos_y -= prm->cam->plane_y * prm->player.mv_spd;
	}
}

void		rotate_left_right(t_prm *prm, int key, double old_dir_x,
									double old_plane_x)
{
	if (key == KEY_Q)
	{
		prm->player.dir_x = prm->player.dir_x * cos(-prm->player.rot_spd) -
								prm->player.dir_y * sin(-prm->player.rot_spd);
		prm->player.dir_y = old_dir_x * sin(-prm->player.rot_spd) +
		prm->player.dir_y * cos(-prm->player.rot_spd);
		prm->cam->plane_x = prm->cam->plane_x * cos(-prm->player.rot_spd) -
								prm->cam->plane_y * sin(-prm->player.rot_spd);
		prm->cam->plane_y = old_plane_x * sin(-prm->player.rot_spd) +
								prm->cam->plane_y * cos(-prm->player.rot_spd);
	}
	if (key == KEY_E)
	{
		prm->player.dir_x = prm->player.dir_x * cos(prm->player.rot_spd) -
								prm->player.dir_y * sin(prm->player.rot_spd);
		prm->player.dir_y = old_dir_x * sin(prm->player.rot_spd) +
								prm->player.dir_y * cos(prm->player.rot_spd);
		prm->cam->plane_x = prm->cam->plane_x * cos(prm->player.rot_spd) -
								prm->cam->plane_y * sin(prm->player.rot_spd);
		prm->cam->plane_y = old_plane_x * sin(prm->player.rot_spd) +
								prm->cam->plane_y * cos(prm->player.rot_spd);
	}
}

void		move_up_down(t_prm *prm, int key)
{
	if (key == KEY_W)
	{
		if (prm->world_map[(int)(prm->player.pos_x + prm->player.dir_x *
			prm->player.mv_spd)][(int)(prm->player.pos_y)] != '1')
			prm->player.pos_x += prm->player.dir_x * prm->player.mv_spd;
		if (prm->world_map[(int)(prm->player.pos_x)][(int)(prm->player.pos_y +
			prm->player.dir_y * prm->player.mv_spd)] != '1')
			prm->player.pos_y += prm->player.dir_y * prm->player.mv_spd;
	}
	if (key == KEY_S)
	{
		if (prm->world_map[(int)(prm->player.pos_x - prm->player.dir_x *
			prm->player.mv_spd)][(int)(prm->player.pos_y)] != '1')
			prm->player.pos_x -= prm->player.dir_x * prm->player.mv_spd;
		if (prm->world_map[(int)(prm->player.pos_x)][(int)(prm->player.pos_y -
			prm->player.dir_y * prm->player.mv_spd)] != '1')
			prm->player.pos_y -= prm->player.dir_y * prm->player.mv_spd;
	}
}

int			keys_hook(int key, t_prm *prm)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = prm->player.dir_x;
	old_plane_x = prm->cam->plane_x;
	if (key == KEY_W || key == KEY_S)
		move_up_down(prm, key);
	if (key == KEY_Q || key == KEY_E)
		rotate_left_right(prm, key, old_dir_x, old_plane_x);
	if (key == KEY_A || key == KEY_D)
		move_left_right(prm, key);
	if (key == KEY_ESC)
		ft_exit(prm);
	return (0);
}
