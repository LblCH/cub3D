/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 01:11:26 by ztawanna          #+#    #+#             */
/*   Updated: 2020/10/29 02:47:01 by ztawanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void		load_level(t_prm *prm, char *name)
{
	int		fd;

	if ((fd = open(name, O_RDONLY)) < 0)
		error_handler(MAP_OPENING_ERR);
	prm->map_str = ft_strdup("");
	prm->map_height = 0;
	prm->map_width = 0;
	parcing(fd, prm);
	close(fd);
	prm->player.dir = '0';
	check_and_set_map(prm);
	init_player(prm);
	prm->tick = 0;
}

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
	free(prm->txtr_sky);
	free(prm->txtr_fl);
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

int			keys_hook(int key, t_prm *prm)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = prm->player.dir_x;
	old_plane_x = prm->cam->plane_x;
	if (key == KEY_W || key == KEY_S)
		move_up(prm, key);
	if (key == KEY_Q || key == KEY_E)
		rotate_left_right(prm, key, old_dir_x, old_plane_x);
	if (key == KEY_A || key == KEY_D)
		move_right(prm, key);
	if (key == KEY_UP || key == KEY_DOWN || key == KEY_C || key == KEY_SPACE)
		look_up_down_jump_crouch(prm, key);
	if (key == KEY_ESC)
		ft_exit(prm);
	if (prm->world_map[(int)prm->player.pos_x][(int)prm->player.pos_y] == 'T')
		load_level(prm, "./maps/map1_bonus.cub");
	return (0);
}
