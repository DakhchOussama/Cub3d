# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mouarsas <mouarsas@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/26 23:33:22 by mouarsas          #+#    #+#              #
#    Updated: 2022/12/26 23:38:44 by mouarsas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = gcc
LIB = libft/libft.a
CFLAGS = -Wall -Werror -Wextra
SRC =	raycasting/free_destroy.c \
		parsing/get_next_line/get_next_line.c \
		parsing/get_next_line/get_next_line_utils.c \
		parsing/check_map.c \
		parsing/pars_map.c \
		parsing/ft_spl.c \
		parsing/utils_map2.c \
		parsing/check_texture.c \
		parsing/utils_map.c \
		raycasting/process_input.c \
		raycasting/setup.c \
		raycasting/draw.c \
		raycasting/castRays.c \
		raycasting/texture.c \
		raycasting/move.c \
		raycasting/render.c \
		raycasting/create.c \
		raycasting/horizontal_Intercestion.c \
		raycasting/vertical_Intercestion.c \
		raycasting/main.c

HEADERS = raycasting/main.h

OBJECTS = $(SRC:.c=.o)

all:$(NAME)

$(LIB):
	@make -C libft

$(NAME): $(LIB) $(OBJECTS)
	@echo "\033[0;33m [Compilation ongoing ...]\033[0;37m"
	$(CC) -lmlx -framework OpenGL -framework AppKit libft/libft.a $(CFLAGS) $(OBJECTS) -o $(NAME)
	@echo "\033[0;32m [Compilation finished ...]\033[0;37m"

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -Imlx -c $< -o $@

clean:
	@make clean -C libft
	rm -f $(OBJECTS)
	rm -f $(OBJECTS_B)
fclean: clean
	@make fclean -C libft
	rm -f $(NAME)
	rm -f $(B_NAME)
re: fclean all

.PHONY: all clean fclean re