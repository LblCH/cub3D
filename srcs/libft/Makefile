# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/28 00:10:49 by ztawanna          #+#    #+#              #
#    Updated: 2020/10/11 19:50:10 by ztawanna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SOURCES	= ft_atoi.c \
		  ft_bzero.c \
		  ft_calloc.c \
		  ft_isalnum.c \
		  ft_isalpha.c \
		  ft_isascii.c \
		  ft_isdigit.c \
		  ft_isprint.c \
		  ft_itoa.c \
		  ft_memccpy.c \
		  ft_memchr.c \
		  ft_memcmp.c \
		  ft_memcpy.c \
		  ft_memmove.c \
		  ft_memset.c \
		  ft_putchar_fd.c \
		  ft_putendl_fd.c \
		  ft_putnbr_fd.c \
		  ft_putstr_fd.c \
		  ft_split.c \
		  ft_strchr.c \
		  ft_strdup.c \
		  ft_strjoin.c \
		  ft_strlcat.c \
		  ft_strlcpy.c \
		  ft_strlen.c \
		  ft_strmapi.c \
		  ft_strncmp.c \
		  ft_strnstr.c \
		  ft_strrchr.c \
		  ft_strtrim.c \
		  ft_substr.c \
		  ft_tolower.c \
		  ft_toupper.c \

OBJECTS		= ${SOURCES:.c=.o}

BSOURCES	= ft_lstnew_bonus.c \
		  ft_lstadd_front_bonus.c \
		  ft_lstadd_back_bonus.c \
		  ft_lstsize_bonus.c \
		  ft_lstlast_bonus.c \
		  ft_lstclear_bonus.c \
		  ft_lstdelone_bonus.c \
		  ft_lstiter_bonus.c \
		  ft_lstmap_bonus.c

BOBJECTS	= ${BSOURCES:.c=.o}

NAME		= libft.a

NAME_SO		= libft.so

CC			= clang
CFLAGS		= -Wall -Wextra -Werror

RM			= rm -f

$(NAME):	${OBJECTS}
			${CC} ${CFLAGS} -c ${SOURCES}
			ar rc ${NAME} ${OBJECTS} libft.h

all:		${NAME}

clean:
			${RM} ${OBJECTS} ${BOBJECTS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

so:
			${CC} $(FLAG) -shared -o $(NAME_SO) -fPIC $(SOURCES)

bonus:		${BOBJECTS}
			${CC} ${CFLAGS} -c ${BSOURCES}
			ar rc ${NAME} ${BOBJECTS} libft.h
