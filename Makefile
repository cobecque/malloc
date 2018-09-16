# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cobecque <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/14 17:49:44 by cobecque          #+#    #+#              #
#    Updated: 2018/09/16 15:22:23 by cobecque         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY:all clean fclean re

NAME = malloc

INC_NAME = ./includes
LIBP_NAME = libftprintf.a
LIB_NAME = libft.a
SRC_NAME = ft_malloc.c

LIB_DIR = ./libft
LIBP_DIR = ./libft/src/printf
SRC_DIR = ./srcs
OBJ_DIR = ./malloc_obj

LIB_PATH = $(addprefix $(LIB_DIR)/,$(LIB_NAME))
LIBP_PATH = $(addprefix $(LIBP_DIR)/,$(LIBP_NAME))
SRC_PATH = $(addprefix $(SRC_DIR)/,$(SRC_NAME))
OBJ_PATH = $(addprefix $(OBJ_DIR)/,$(SRC_NAME:.c=.o))

CC = gcc
FLAGS = -Wall -Werror -Wextra #-fsanitize=address -g3

all :
	@clear
	@printf $(CN_MAG) "=== ->  Compil all libs  <- ==="
	@make -C $(LIBP_DIR)
	@printf "\n"
	@printf $(CN_YEL) "=== ->  Compil assembleur  <- ==="
	@mkdir -p malloc_obj
	@$(MAKE) $(NAME)

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c
	@$(CC) $(FLAGS) -I $(INC_NAME) -o $@ -c $<
	@printf $(C_BLU) "        [ ✔ ] $<"

$(NAME): $(OBJ_PATH)
	@$(CC) $(FLAGS) $(OBJ_PATH) $(LIB_PATH) $(LIBP_PATH) -o $(NAME)
	@printf $(C_CYA) "        [ ✔ ] compiled → $(NAME)"
	@printf "\n"

clean :
	@printf "\n"
	@printf $(CN_YEL) "=================   MALLOC   ================="
	@make clean -C $(LIBP_DIR)
	@/bin/rm -f $(OBJ_PATH)
	@rm -rf ./malloc_obj
	@printf $(C_RED) " [ ✔ ] deleted objects path"
	@printf "\n"

fclean : clean
	@printf "\n"
	@rm -f $(LIBP_PATH)
	@rm -f $(LIB_PATH)
	@/bin/rm -f $(NAME)
	@printf $(C_RED) " [ ✔ ] deleted binary file → $(NAME)"
	@printf "\n"

re: fclean all

# color
C_RED = "\e[31;m%s\e[0m\n"
C_GRN = "\e[32;m%s\e[0m\n"
C_YEL = "\e[33;m%s\e[0m\n"
C_BLU = "\e[34;m%s\e[0m\n"
C_MAG = "\e[35;m%s\e[0m\n"
C_CYA = "\e[36;m%s\e[0m\n"

# color + \n

CN_RED = "\e[31;m%s\e[0m\n\n"
CN_GRN = "\e[32;m%s\e[0m\n\n"
CN_YEL = "\e[33;m%s\e[0m\n\n"
CN_BLU = "\e[34;m%s\e[0m\n\n"
CN_MAG = "\e[35;m%s\e[0m\n\n"
CN_CYA = "\e[36;m%s\e[0m\n\n"
