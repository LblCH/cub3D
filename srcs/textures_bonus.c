/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 02:24:42 by ztawanna          #+#    #+#             */
/*   Updated: 2020/10/29 02:11:15 by ztawanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void		draw_sky(t_prm *prm, int x, int y)
{
	int color;

	color = prm->txtr_sky->data[prm->txtr_sky->w * (y *
		prm->txtr_sky->h / (prm->height * 3 / 4)) +
		(x * prm->txtr_sky->w / prm->width)];
	*(prm->screen->data + (y * prm->width) + x) = color;
}

void		set_texture(char *file, t_prm *prm)
{
	int		i;

	i = 2;
	while (ft_isspace(file[i]))
		i++;
	if (open(&file[i], O_RDONLY) < 0)
		error_handler(TEXTURE_ERR);
	if (*file == 'N' && *(file + 1) == 'O' && *prm->txtr_n->data == 0)
		memorize_texture(prm->txtr_n, prm, &file[i]);
	else if (*file == 'S' && *(file + 1) == 'O' && *prm->txtr_s->data == 0)
		memorize_texture(prm->txtr_s, prm, &file[i]);
	else if (*file == 'W' && *(file + 1) == 'E' && *prm->txtr_w->data == 0)
		memorize_texture(prm->txtr_w, prm, &file[i]);
	else if (*file == 'E' && *(file + 1) == 'A' && *prm->txtr_e->data == 0)
		memorize_texture(prm->txtr_e, prm, &file[i]);
	else if (*file == 'S' && *(file + 1) == ' ' && *prm->txtr_spr->data == 0)
		memorize_texture(prm->txtr_spr, prm, &file[i]);
	else if (*file == 'S' && *(file + 1) == 'B' && *prm->txtr_sky->data == 0)
		memorize_texture(prm->txtr_sky, prm, &file[i]);
	else if (*file == 'F' && *(file + 1) == 'L')
		memorize_texture(prm->txtr_fl, prm, &file[i]);
	else
		error_handler(TEXTURE_ERR);
}

void		set_wall_texture(t_prm *prm)
{
	(prm->cam->side == 0) ? (prm->cam->wall_x = prm->player.pos_y +
		prm->cam->wall_dist * prm->cam->ray_dir_y) : (prm->cam->wall_x =
		prm->player.pos_x + prm->cam->wall_dist * prm->cam->ray_dir_x);
	prm->cam->wall_x -= floor((prm->cam->wall_x));
	prm->screen->txtr_x = (int)(prm->cam->wall_x *
		(double)(prm->screen->txtr->w));
	if (prm->cam->side == 0 && prm->cam->ray_dir_x > 0)
		prm->screen->txtr_x = prm->screen->txtr->w - prm->screen->txtr_x - 1;
	if (prm->cam->side == 1 && prm->cam->ray_dir_y < 0)
		prm->screen->txtr_x = prm->screen->txtr->w - prm->screen->txtr_x - 1;
	prm->screen->step = 1.0 * prm->screen->txtr->h / prm->screen->line_h;
	prm->screen->txtr_pos = (prm->screen->l_start - prm->height / 2 -
		prm->player.pitch - prm->player.pos_z / prm->cam->wall_dist +
		prm->screen->line_h / 2) * prm->screen->step;
}

void		get_texture(t_prm *prm)
{
	if (prm->cam->side == 1)
	{
		if ((prm->cam->y - prm->player.pos_y) > 0)
			prm->screen->txtr = prm->txtr_n;
		else
			prm->screen->txtr = prm->txtr_s;
	}
	else
	{
		if ((prm->cam->x - prm->player.pos_x) > 0)
			prm->screen->txtr = prm->txtr_w;
		else
			prm->screen->txtr = prm->txtr_e;
	}
}

void		memorize_texture(t_texture *txtr, t_prm *prm, char *file)
{
	if ((txtr->img = mlx_xpm_file_to_image(prm->mlx_ptr, file,
		&txtr->w, &txtr->h)) == 0)
		error_handler(VALID_TEXT_ERR);
	free(txtr->data);
	txtr->data = (int*)mlx_get_data_addr(txtr->img, &txtr->bpp,
		&txtr->size_l, &txtr->endian);
}
