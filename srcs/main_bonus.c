/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 00:18:55 by ztawanna          #+#    #+#             */
/*   Updated: 2020/10/29 01:19:04 by ztawanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void		load_game(char *name, int save)
{
	int		fd;
	t_prm	prm;

	prm.mlx_ptr = mlx_init();
	init_strusture(&prm);
	if ((fd = open(name, O_RDONLY)) < 0)
		error_handler(MAP_OPENING_ERR);
	parcing(fd, &prm);
	close(fd);
	check_and_set_map(&prm);
	init_player(&prm);
	prm.mlx_ptr = mlx_init();
	prm.win_ptr = mlx_new_window(prm.mlx_ptr, prm.width, prm.height, "Cub3D");
	prm.screen->img = mlx_new_image(prm.mlx_ptr, prm.width, prm.height);
	prm.screen->data = (int*)mlx_get_data_addr(prm.screen->img,
				&prm.screen->bpp, &prm.screen->size_l, &prm.screen->endian);
	prm.save = (save == 1) ? 1 : 0;
	prm.tick = 0;
	start_render(&prm);
	mlx_do_key_autorepeaton(prm.mlx_ptr);
	mlx_hook(prm.win_ptr, 2, 1, keys_hook, &prm);
	mlx_loop_hook(prm.mlx_ptr, start_render, &prm);
	mlx_hook(prm.win_ptr, 17, 1, ft_exit, &prm);
	mlx_loop(prm.mlx_ptr);
}

int			check_args(char *name, char *save)
{
	int		i;

	i = ft_strlen(name);
	if (ft_memcmp(&name[i - 4], ".cub", 4) == 0 &&
		(ft_memcmp(save, "--save", 6) == 0 || ft_memcmp(save, "none", 4) == 0))
		return (1);
	return (0);
}

int			main(int argc, char **argv)
{
	if (argc == 3 && check_args(argv[1], argv[2]))
		load_game(argv[1], 1);
	else if (argc == 2 && check_args(argv[1], "none"))
		load_game(argv[1], 0);
	else
		error_handler(ARGUMENTS_ERR);
	return (0);
}
