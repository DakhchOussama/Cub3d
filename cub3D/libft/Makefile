# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mouarsas <mouarsas@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/11 23:09:21 by mouarsas          #+#    #+#              #
#    Updated: 2022/12/26 21:23:14 by mouarsas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC =	ft_strncmp.c\
		ft_strdup.c\
		ft_split.c\
		ft_strlen.c\
		ft_strjoin.c \
		ft_strtrim.c\
		ft_strchr.c\
		ft_strcmp.c\
		ft_atoi.c \
		ft_substr.c \
		ft_strlcpy.c \
		ft_isdigit.c\

OBJECTS = $(SRC:.c=.o)


all: $(NAME)

$(NAME): $(OBJECTS)
	ar rc $(NAME) $(OBJECTS)

%.o : %.c libft.h
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJECTS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
