/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 05:03:33 by ztawanna          #+#    #+#             */
/*   Updated: 2020/10/22 21:01:57 by ztawanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		my_mlx_pixel_put(t_screen *img, int x, int y, int color)
{
	int	*dst;

	dst = img->data + (y * img->size_l + x);
	*dst = color;
}

int			start_render(t_prm *prm)
{
	wall_calculation(prm);
	sprites_casting(prm);
	if (prm->save == 0)
		mlx_put_image_to_window(prm->mlx_ptr, prm->win_ptr,
													prm->screen->img, 0, 0);
	else
		save_bmp(prm);
	return (0);
}
