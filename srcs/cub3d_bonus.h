/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 01:14:28 by ztawanna          #+#    #+#             */
/*   Updated: 2020/10/29 02:41:19 by ztawanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "./minilibx/mlx.h"
# include "./libft/libft.h"
# include "./gnl/get_next_line.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <mlx.h>

# define KEY_Q 12
# define KEY_W 13
# define KEY_E 14
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_E 14
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_ESC 53
# define KEY_SPACE 49
# define KEY_C 8

# define MALLOC_ERR 0
# define MAP_OPENING_ERR 1
# define MAP_FILE_ERR 2
# define ARGUMENTS_ERR 3
# define COLOR_ERR 4
# define VALID_TEXT_ERR 5
# define RESOL_ERR 6
# define TEXTURE_ERR 7
# define BAD_MAP_ERR 8
# define CREATE_ERR 9

# define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
# define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

typedef struct	s_player
{
	char		dir;
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		mv_spd;
	double		rot_spd;
	int			pos_z;
	int			pitch;
}				t_player;

typedef	struct	s_texture
{
	void		*img;
	int			*data;
	int			bpp;
	int			size_l;
	int			endian;
	int			w;
	int			h;
	void		*img2;
	int			*data2;
	int			bpp2;
	int			size_l2;
	int			endian2;
	int			w2;
	int			h2;
	void		*imgt;
	int			*datat;
	int			bppt;
	int			size_lt;
	int			endiant;
	int			wt;
	int			ht;
}				t_texture;

typedef	struct	s_screen
{
	void		*img;
	int			*data;
	int			bpp;
	int			size_l;
	int			endian;
	int			line_h;
	int			l_start;
	int			l_end;
	t_texture	*txtr;
	int			txtr_x;
	int			txtr_y;
	double		step;
	double		txtr_pos;
}				t_screen;

typedef struct	s_cam
{
	int			x;
	int			y;
	double		cam_x;
	double		ray_dir_x;
	double		ray_dir_y;
	double		plane_x;
	double		plane_y;
	double		side_x;
	double		side_y;
	double		delta_x;
	double		delta_y;
	double		wall_dist;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	double		wall_x;
	double		*z_buff;
	float		ray_dir_x0;
	float		ray_dir_y0;
	float		ray_dir_x1;
	float		ray_dir_y1;
	float		pos_z;
	float		fl_st_x;
	float		fl_st_y;
	float		fl_x;
	float		fl_y;
}				t_cam;

typedef struct	s_sprite
{
	int			num;
	int			*order;
	double		*distance;
	double		*x;
	double		*y;
	int			*used;
	double		trnfm_x;
	double		trnfm_y;
	double		pos_x;
	double		pos_y;
	int			screen_x;
	int			height;
	int			width;
	int			start_x;
	int			end_x;
	int			start_y;
	int			end_y;
	int			txtr_x;
	int			txtr_y;
	int			vms;
}				t_sprite;

typedef struct	s_prm
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			width;
	int			height;
	int			floor_color;
	int			ceiling_color;
	int			map_width;
	int			map_height;
	char		*map_str;
	char		**world_map;
	double		inv_det;
	t_cam		*cam;
	t_screen	*screen;
	t_texture	*txtr_n;
	t_texture	*txtr_s;
	t_texture	*txtr_w;
	t_texture	*txtr_e;
	t_texture	*txtr_spr;
	t_texture	*txtr_sky;
	t_texture	*txtr_fl;
	t_player	player;
	t_sprite	*sprite;
	int			save;
	int			tick;
	void		*l_img;
	int			*l_data;
	int			a[5];
}				t_prm;

/*
** main.c
*/
void			load_game(char *name, int save);
int				check_args(char *name, char *save);
void			load_game(char *name, int save);

/*
** parcer.c
*/
void			parcing(int fd, t_prm *prm);
void			init_floor_n_ceiling(char *line, t_prm *prm, int i);
void			init_floor_n_ceiling2(char c, t_prm *prm, int x, int rgb);
void			init_resolution(char *line, t_prm *prm);
void			init_map(char *line, t_prm *prm);

/*
** check_and_set.c
*/
void			check_and_set_map(t_prm *prm);
void			check_params(t_prm *prm);
void			check_and_set_pos(t_prm *prm, int i, int j, int z);
void			check_map(t_prm *prm);

/*
**textures.c
*/
void			set_wall_texture(t_prm *prm);
void			get_texture(t_prm *prm);
void			memorize_texture(t_texture *txtr, t_prm *prm, char *file);
void			set_texture(char *file, t_prm *prm);
void			draw_sky(t_prm *prm, int x, int y);

/*
**render.c
*/
int				get_shadow(t_prm *prm, int color, int x, int y);
int				start_render(t_prm *prm);
void			draw_map(t_prm *prm);
void			my_mlx_pixel_put(t_screen *img, int x, int y, int color);
void			draw_life(t_prm *prm, int y);

/*
**wall.c
*/
void			wall_calculation(t_prm *prm);
void			hit_test(t_prm *prm);
void			calc_step_and_side(t_prm *prm);
void			wall_height(t_prm *prm);
void			draw_wall(t_prm *prm, int x);

/*
**sprites.c
*/
void			sprites_casting(t_prm *prm);
void			get_sprites_coord(t_prm *prm, int i);
int				get_active_spr_index(t_prm *prm);
void			get_sprite_height_draw(t_prm *prm, int i);
void			draw_sprite(t_prm *prm, int stripe, int i);

/*
**utils.c
*/
void			error_handler(int err);
void			sprites_init(t_prm *prm);
void			calloc_structures(t_prm *prm);
void			init_strusture(t_prm *prm);
void			init_player(t_prm *prm);

/*
**keys.c
*/
int				keys_hook(int key, t_prm *prm);
void			rotate_left_right(t_prm *prm, int key, double old_dir_x,
									double old_plane_x);
int				ft_exit(t_prm *prm);
void			load_level(t_prm *prm, char *name);

/*
**keys2.c
*/
void			look_up_down_jump_crouch(t_prm *prm, int key);
void			move_up(t_prm *prm, int key);
void			move_down(t_prm *prm);
void			move_left(t_prm *prm);
void			move_right(t_prm *prm, int key);

/*
**save_bmp.c
*/
void			save_bmp(t_prm *prm);
static void		bmp_header(t_prm *prm, int fd);

/*
**floor.c
*/
void			floor_raycasting(t_prm *prm);
void			draw_floor(t_prm *prm, int y, int x);
int				get_sprite_pixel(t_prm *prm, int i, int d, int stripe);
int				draw_teleport(t_prm *prm, int i, int d, int stripe);
#endif
