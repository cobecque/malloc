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

NAME = libft_malloc_$(HOSTTYPE).so

INC_NAME = ./includes
SRC = src/malloc.c \
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

SRC_DIR = ./src
OBJ_DIR = ./obj
LIB_DIR = ./libft
LIBP_DIR = ./libft/src/printf

LIB_PATH = $(addprefix $(LIB_DIR)/, $(LIB_NAME))
LIBP_PATH = $(addprefix $(LIBP_DIR)/, $(LIBP_NAME))
SRC_PATH = $(addprefix $(SRC_DIR)/, $(SRC_NAME))
OBJ_PATH = $(addprefix $(OBJ_DIR)/, $(SRC_NAME:.c=.o))

export HOSTTYPE=

ifeq ($(HOSTTYPE), )
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

FLAG = -Wall -Werror -Wextra -lncurses #-fsanitize=address -g3

all:
	@clear
	@make -C $(LIBP_DIR)
	@mkdir -p $(OBJ_DIR)

	@$(MAKE) $(NAME)

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c
	@gcc $(FLAG) -I $(INC_NAME) -o $@ -c $<
	@printf $(C_MAG) "        [ ✔ ] $<"

$(NAME): $(OBJ_PATH)
	gcc -o $(NAME) -L $(OBJ_PATH) -shared  2>/dev/null
	printf $(C_GRN) "        [ ✔ ] compiled -> $(NAME)"



clean:
	@make clean -C $(LIBP_DIR)
	@rm -rf ./obj

fclean: clean
	@rm -rf $(LIBP_PATH)
	@rm -rf $(LIB_PATH)
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re

# color
C_RED = "\e[31;m%s\e[0n\n"
C_GRN = "\e[32;m%s\e[0n\n"
C_YEL = "\e[33;m%s\e[0n\n"
C_BLU = "\e[34;m%s\e[0n\n"
C_MAG = "\e[35;m%s\e[0n\n"
C_CYA = "\e[36;m%s\e[0n\n"

# color + \n
CN_RED = "\e[31;m%s\e[0n\n\n"
CN_GRN = "\e[32;m%s\e[0n\n\n"
CN_YEL = "\e[33;m%s\e[0n\n\n"
CN_BLU = "\e[34;m%s\e[0n\n\n"
CN_MAG = "\e[35;m%s\e[0n\n\n"
CN_CYA = "\e[36;m%s\e[0n\n\n"