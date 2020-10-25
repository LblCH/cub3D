/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 05:03:33 by ztawanna          #+#    #+#             */
/*   Updated: 2020/10/24 20:20:52 by ztawanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void		draw_life(t_prm *prm, int y)
{
	int		x;
	int		color;

	while (y < (prm->height * 1 / 4))
	{
		x = prm->width * 3 / 4;
		while (x < prm->width)
		{
			color = prm->l_data[prm->a[1] * (y * prm->a[2] /
				(prm->height / 4)) + x * prm->a[1] / (prm->width / 4)];
			if (color != prm->l_data[0])
				*(prm->screen->data + (y * prm->width) + x) = color;
			x++;
		}
		y++;
	}
}

int			get_shadow(t_prm *prm, int color, int x, int y)
{
	int r;
	int g;
	int b;
	int dist;

	dist = sqrt(pow((prm->player.pos_x - x), 2) +
											pow((prm->player.pos_y - y), 2));
	if (dist < 5)
		dist = 1;
	else if (dist < 10)
		dist = 2;
	else
		dist = 3;
	r = (((color >> 16) & 0xFF) & 0xFF) / (dist);
	g = (((color >> 8) & 0xFF) & 0xFF) / (dist);
	b = (((color) & 0xFF) & 0xFF) / (dist);
	return (r << 16 | g << 8 | b);
}

void		my_mlx_pixel_put(t_screen *img, int x, int y, int color)
{
	int	*dst;

	dst = img->data + (y * img->size_l + x);
	*dst = color;
}

void		draw_map(t_prm *prm)
{
	int w_scale;
	int h_scale;
	int i;
	int j;

	i = 0;
	w_scale = prm->width / (4 * prm->map_width);
	h_scale = prm->height / (4 * prm->map_height);
	while (i / w_scale < prm->map_width)
	{
		j = 0;
		while ((j / h_scale) < prm->map_height)
		{
			if (prm->world_map[i / w_scale][j / h_scale] == '1')
				*(prm->screen->data + (j * prm->width) + i) = 0xFDFF0000;
			else if (prm->world_map[i / w_scale][j / h_scale] == '2')
				*(prm->screen->data + (j * prm->width) + i) = 0xFD00FFFF;
			j++;
		}
		i++;
	}
	*(prm->screen->data + (int)(prm->player.pos_y * h_scale * prm->width) +
		(int)prm->player.pos_x * w_scale) = 0x008735ff;
}

int			start_render(t_prm *prm)
{
	int y;

	floor_raycasting(prm);
	wall_calculation(prm);
	sprites_casting(prm);
	draw_map(prm);
	y = 0;
	draw_life(prm, y);
	(prm->player.pitch > 0) ? prm->player.pitch = MAX(0, prm->player.pitch -
		prm->height / 30 * prm->player.mv_spd) : (0);
	(prm->player.pitch < 0) ? prm->player.pitch = MIN(0, prm->player.pitch +
		prm->height / 30 * prm->player.mv_spd) : (0);
	(prm->player.pos_z > 0) ? prm->player.pos_z = MAX(0, prm->player.pos_z -
		prm->height / 20 * prm->player.mv_spd) : (0);
	(prm->player.pos_z < 0) ? prm->player.pos_z = MIN(0, prm->player.pos_z +
		prm->height / 30 * prm->player.mv_spd) : (0);
	if (prm->save == 0)
		mlx_put_image_to_window(prm->mlx_ptr, prm->win_ptr,
													prm->screen->img, 0, 0);
	else
		save_bmp(prm);
	if (++prm->tick > 3)
		prm->tick = 0;
	return (0);
}
