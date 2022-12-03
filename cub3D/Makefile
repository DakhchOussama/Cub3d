CC = gcc
CFLAGS = -Wall -Werror -Wextra
NAME = cub
SRC = src/ft_split.c src/ft_strdup.c src/ft_strjoin.c  \
	src/free_destroy.c \
	src/process_input.c \
	src/setup_map.c \
	src/castRays.c \
	src/texture.c \
	src/checkWall.c \
	src/read_file.c \
	src/move.c \
	src/render.c \
	src/draw.c \
	src/create.c \
	src/hori_vert-Intercestion.c \
	src/main.c


OBJECTS = $(SRC:.c=.o)

all:$(NAME)

$(NAME):$(OBJECTS)
	@echo "\033[0;33m [Compilation ongoing ...]\033[0;37m"
	$(CC) -lmlx -framework OpenGL -framework AppKit $(CFLAGS) $(OBJECTS) -o $(NAME)
	@echo "\033[0;32m [Compilation finished ...]\033[0;37m"
%.o: %.c $(SRC)
	$(CC) $(CFLAGS) -Imlx -c $< -o $@
clean:
	rm -f $(OBJECTS)
	rm -f $(OBJECTS_B)
fclean: clean
	rm -f $(NAME)
	rm -f $(B_NAME)
re: fclean all

.PHONY: all clean fclean re