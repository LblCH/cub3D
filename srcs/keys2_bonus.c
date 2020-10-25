/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys2_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 11:00:55 by ztawanna          #+#    #+#             */
/*   Updated: 2020/10/23 20:13:31 by ztawanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
