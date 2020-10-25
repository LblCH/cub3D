# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/08 00:19:12 by ztawanna          #+#    #+#              #
#    Updated: 2020/10/23 20:22:09 by ztawanna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Cub3D

NAME_BONUS = Cub3D_bonus

CC = clang

GCC_FLAGS	= -Wall -Wextra -Werror

SRCS =	./srcs/main.c \
		./srcs/parcer.c \
		./srcs/utils.c \
		./srcs/keys.c \
		./srcs/check_and_set.c \
		./srcs/render.c \
		./srcs/textures.c \
		./srcs/walls.c \
		./srcs/sprites.c \
		./srcs/save_bmp.c \
		./srcs/gnl/get_next_line.c \
		./srcs/gnl/get_next_line_utils.c

SRCS_BONUS = ./srcs/main_bonus.c \
		./srcs/parcer_bonus.c \
		./srcs/utils_bonus.c \
		./srcs/keys_bonus.c \
		./srcs/keys2_bonus.c \
		./srcs/check_and_set_bonus.c \
		./srcs/render_bonus.c \
		./srcs/textures_bonus.c \
		./srcs/walls_bonus.c \
		./srcs/sprites_bonus.c \
		./srcs/save_bmp_bonus.c \
		./srcs/floor_bonus.c \
		./srcs/gnl/get_next_line.c \
		./srcs/gnl/get_next_line_utils.c

OBJS = $(SRCS:.c=.o)

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

$(%.o): $(%.c)
	$(CC) -o $@ -c $^

LXFLAGS = -lmlx -framework OPENGL -framework Appkit

all: $(NAME)

$(NAME): $(OBJS)
	@make -C ./srcs/libft
	@make -C ./srcs/minilibx
	@cp -a ./srcs/minilibx/libmlx.dylib ./
	@$(CC) $(GCC_FLAGS) -g $(LXFLAGS) srcs/minilibx/libmlx.dylib \
	srcs/libft/libft.a -o $@ $^


bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJS_BONUS)
	@make -C ./srcs/libft
	@make -C ./srcs/minilibx
	@cp -a ./srcs/minilibx/libmlx.dylib ./
	@$(CC) $(GCC_FLAGS) $(LXFLAGS) srcs/minilibx/libmlx.dylib \
	srcs/libft/libft.a -o $@ $^

clean:
	@rm -rf $(OBJS) $(OBJS_BONUS)
	@make -C ./srcs/libft clean
	@rm -f bitmap.bmp

fclean: clean
	@make -C ./srcs/libft fclean
	@make -C ./srcs/minilibx clean
	@rm -rf ./libmlx.dylib
	@rm -f $(NAME) $(NAME_BONUS)

re: fclean all

bonus_re: fclean bonus
