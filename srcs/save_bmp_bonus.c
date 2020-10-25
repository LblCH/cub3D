/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_bmp_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 11:48:07 by ztawanna          #+#    #+#             */
/*   Updated: 2020/10/23 17:25:55 by ztawanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	bmp_dib_header(int fd, int file_size)
{
	int aux;

	write(fd, "BM", 2);
	write(fd, &file_size, 4);
	aux = 0;
	write(fd, &aux, 4);
	aux = 14 + 40;
	write(fd, &aux, 4);
}

static void	bmp_header(t_prm *prm, int fd)
{
	int file_size;
	int aux;

	aux = prm->width * prm->height;
	file_size = (4 + 54) * aux;
	bmp_dib_header(fd, file_size);
	aux = 40;
	write(fd, &aux, 4);
	write(fd, &prm->width, 4);
	write(fd, &prm->height, 4);
	aux = 1;
	write(fd, &aux, 2);
	aux = 32;
	write(fd, &aux, 2);
	aux = 0;
	write(fd, &aux, 4);
	write(fd, &file_size, 4);
	aux = 2835;
	write(fd, &aux, 4);
	write(fd, &aux, 4);
	aux = 0;
	write(fd, &aux, 8);
}

void		save_bmp(t_prm *prm)
{
	int fd;
	int res;
	int i;
	int j;

	res = 0;
	if ((fd = open("Cub3D.bmp", O_CREAT | O_WRONLY | O_TRUNC, 0644)) < 0)
		error_handler(CREATE_ERR);
	else
	{
		bmp_header(prm, fd);
		i = -1;
		while (++i < prm->height)
		{
			j = -1;
			while (++j < prm->width)
			{
				res = *(prm->screen->data + (prm->width *
					(prm->height - 1 - i) + j));
				write(fd, &res, 4);
			}
		}
	}
	close(fd);
	ft_exit(prm);
}
