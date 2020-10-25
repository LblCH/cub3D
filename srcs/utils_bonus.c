/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 09:10:08 by ztawanna          #+#    #+#             */
/*   Updated: 2020/10/25 18:44:06 by ztawanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void		error_handler(int err)
{
	if (err == TEXTURE_ERR)
		write(2, "Error\nTexture error.", 20);
	if (err == MAP_OPENING_ERR)
		write(2, "Error\nError in map opening.", 27);
	if (err == MAP_FILE_ERR)
		write(2, "Error\nWrong map file.", 21);
	if (err == ARGUMENTS_ERR)
		write(2, "Error\nIncorrect arguments.", 26);
	if (err == COLOR_ERR)
		write(2, "Error\nFloor or ceiling color incorrect.", 38);
	if (err == VALID_TEXT_ERR)
		write(2, "Error\nNot valid texture file.", 29);
	if (err == RESOL_ERR)
		write(2, "Error\nResolution error.", 23);
	if (err == BAD_MAP_ERR)
		write(1, "Error\nMap is not correct.", 25);
	if (err == MALLOC_ERR)
		write(2, "Error\nMemory allocation error.", 30);
	if (err == CREATE_ERR)
		write(2, "Error\nError, when creating file.", 32);
	exit(0);
}

void		sprites_init(t_prm *prm)
{
	prm->player.pos_z = 0;
	prm->player.pitch = 0;
	if (!(prm->sprite->used = (int*)malloc(sizeof(int) * prm->sprite->num)))
		error_handler(MALLOC_ERR);
	if (!(prm->sprite->distance = (double*)malloc(sizeof(double)
														* prm->sprite->num)))
		error_handler(MALLOC_ERR);
	if (!(prm->sprite->x = (double*)malloc(sizeof(double) * prm->sprite->num)))
		error_handler(MALLOC_ERR);
	if (!(prm->sprite->y = (double*)malloc(sizeof(double) * prm->sprite->num)))
		error_handler(MALLOC_ERR);
	if (!(prm->cam->z_buff = (double*)malloc(sizeof(double) * prm->width)))
		error_handler(MALLOC_ERR);
	prm->txtr_spr->img2 = mlx_xpm_file_to_image(prm->mlx_ptr,
		"./textures/diamond.xpm", &prm->txtr_spr->w2, &prm->txtr_spr->h2);
	prm->txtr_spr->data2 = (int*)mlx_get_data_addr(prm->txtr_spr->img2,
		&prm->txtr_spr->bpp2, &prm->txtr_spr->size_l2,
		&prm->txtr_spr->endian2);
	prm->l_img = mlx_xpm_file_to_image(prm->mlx_ptr, "./textures/life.xpm",
						&prm->a[1], &prm->a[2]);
	prm->l_data = (int*)mlx_get_data_addr(prm->l_img, &prm->a[3],
						&prm->a[4], &prm->a[5]);
	get_sprites_coord(prm);
}

void		calloc_structures(t_prm *prm)
{
	if (!(prm->txtr_n = ft_calloc(1, sizeof(t_texture))))
		error_handler(MALLOC_ERR);
	if (!(prm->txtr_s = ft_calloc(1, sizeof(t_texture))))
		error_handler(MALLOC_ERR);
	if (!(prm->txtr_w = ft_calloc(1, sizeof(t_texture))))
		error_handler(MALLOC_ERR);
	if (!(prm->txtr_e = ft_calloc(1, sizeof(t_texture))))
		error_handler(MALLOC_ERR);
	if (!(prm->txtr_spr = ft_calloc(1, sizeof(t_texture))))
		error_handler(MALLOC_ERR);
	if (!(prm->txtr_sky = ft_calloc(1, sizeof(t_texture))))
		error_handler(MALLOC_ERR);
	if (!(prm->txtr_fl = ft_calloc(1, sizeof(t_texture))))
		error_handler(MALLOC_ERR);
	if (!(prm->screen = ft_calloc(1, sizeof(t_screen))))
		error_handler(MALLOC_ERR);
	if (!(prm->sprite = ft_calloc(1, sizeof(t_sprite))))
		error_handler(MALLOC_ERR);
}

void		init_strusture(t_prm *prm)
{
	calloc_structures(prm);
	prm->width = 0;
	prm->height = 0;
	prm->floor_color = -1;
	prm->ceiling_color = -1;
	prm->txtr_n->data = (int *)ft_strdup("");
	prm->txtr_s->data = (int *)ft_strdup("");
	prm->txtr_w->data = (int *)ft_strdup("");
	prm->txtr_e->data = (int *)ft_strdup("");
	prm->txtr_spr->data = (int *)ft_strdup("");
	prm->txtr_sky->data = (int *)ft_strdup("");
	prm->txtr_fl->data = (int *)ft_strdup("");
	prm->map_str = ft_strdup("");
	prm->map_width = 0;
	prm->map_height = 0;
	prm->player.dir = '0';
}

void		init_player(t_prm *prm)
{
	if (!(prm->cam = ft_calloc(1, sizeof(t_cam))))
		error_handler(MALLOC_ERR);
	if (prm->player.dir == 'N')
	{
		prm->player.dir_y = -1;
		prm->cam->plane_x = 0.66;
	}
	if (prm->player.dir == 'S')
	{
		prm->player.dir_y = 1;
		prm->cam->plane_x = -0.66;
	}
	if (prm->player.dir == 'E')
	{
		prm->player.dir_x = 1;
		prm->cam->plane_y = 0.66;
	}
	if (prm->player.dir == 'W')
	{
		prm->player.dir_x = -1;
		prm->cam->plane_y = -0.66;
	}
	prm->player.mv_spd = 0.35;
	prm->player.rot_spd = prm->player.mv_spd / 3;
	sprites_init(prm);
}
