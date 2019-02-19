# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rostroh <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/04 15:17:16 by rostroh           #+#    #+#              #
#    Updated: 2019/02/19 01:01:24 by rostroh          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = src/main.c \
	  src/malloc.c \
	  src/realloc.c \
	  src/header.c \
	  src/write_and_read.c \
	  src/release_memory.c \
	  src/check_memory.c \
	  src/tiny.c \
	  src/show.c \
	  src/small.c \
	  src/large.c \
	  src/clear_area.c \
	  src/type.c

LIB_FT = ./libft/libft.a

LIB_PRINTF = ./libft/src/printf/libftprintf.a

FLG = -Wall -Werror -Wextra -lncurses -fsanitize=address -g3

NAME = malloc

all: $(NAME)

$(NAME): $(SRC) $(SRC_MD5) $(SRC_SHA256)
	make -C ./libft
	gcc $(FLAG) -o $(NAME) $(SRC) -I includes $(LIB_FT) $(LIB_PRINTF)

clean:
	make clean -C ./libft

fclean: clean
	make fclean -C ./libft/
	rm -f $(NAME)

re: fclean all
