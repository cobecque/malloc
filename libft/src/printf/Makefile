# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cobecque <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/10 21:13:34 by cobecque          #+#    #+#              #
#    Updated: 2018/03/09 15:25:29 by cobecque         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY:all clean fclean re

NAME = libftprintf.a

INC_NAME = ./../../../includes
LIB_NAME = libft.a
SRC_NAME = conv.c	space.c	print.c	params.c	gestion.c	get_base.c\
		   ft_printf.c	condition.c	ft_putwchar.c	gestion_print.c\
		   wchar_fonction.c	shitty_fonction.c	binary_to_decimal.c\
		   more_shitty_fonction.c

LIB_DIR = ./../../../libft
SRC_DIR = ./src
OBJ_DIR = ./obj_printf
OBJ_LIB = ./obj

LIB_PATH = $(addprefix $(LIB_DIR)/,$(LIB_NAME))
SRC_PATH = $(addprefix $(SRC_DIR)/,$(SRC_NAME))
OBJ_PATH = $(addprefix $(OBJ_DIR)/,$(SRC_NAME:.c=.o))

CC = gcc
FLAGS = -Wall -Werror -Wextra

all:
	@printf $(CN_YEL) "=== ->  Compil libs  <- ==="
	@make -C $(LIB_DIR)
	@printf "\n"
	@printf $(CN_YEL) "=== ->  Compil printf <- ==="
	@mkdir -p obj_printf
	@$(MAKE) $(NAME)

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c
	@$(CC) $(FLAGS) -I $(INC_NAME) -o $@ -c $<
	@printf $(C_BLU) "        [ ✔ ] $<"

$(NAME): $(OBJ_PATH)
	@ar -q $(NAME) $(OBJ_PATH) 2>/dev/null
	@printf $(C_CYA) "        [ ✔ ] compiled → $(NAME)"
	@printf "\n"

clean :
	@printf "\n"
	@make clean -C $(LIB_DIR)
	@/bin/rm -f $(OBJ_PATH)
	@rm -rf ./obj_printf
	@printf $(C_RED) " [ ✔ ] deleted objects path"
	@printf "\n"

fclean : clean
	@printf "\n"
	@rm -f $(LIB_PATH)
	@/bin/rm -f $(NAME)
	@printf $(C_RED) " [ ✔ ] deleted binary file → $(NAME)"
	@printf "\n"

re: fclean all

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
	  #libft/ft_atoi.c\
	  libft/ft_isspace.c\
	  libft/ft_isdigit.c \
	  libft/ft_long_itoa.c \
	  libft/ft_putchar.c \
	  libft/ft_putstr.c \
	  libft/ft_strcmp.c \
	  libft/ft_strcpy.c \
	  libft/ft_strjoin.c \
	  libft/ft_strlen.c \
	  libft/ft_strnew.c \
	  libft/ft_strrev.c \
	  libft/ft_strsub.c

#OBJ = conv.o \
	  space.o \
	  print.o \
	  params.o \
	  gestion.o \
	  get_base.o \
	  ft_printf.o \
	  condition.o \
	  ft_putwchar.o \
	  gestion_print.o \
	  wchar_fonction.o \
	  shitty_fonction.o \
	  binary_to_decimal.o \
	  more_shitty_fonction.o \
	  ft_atoi.o \
	  ft_isspace.o \
	  ft_isdigit.o \
	  ft_long_itoa.o \
	  ft_putchar.o \
	  ft_putstr.o \
	  ft_strcmp.o \
	  ft_strcpy.o \
	  ft_strjoin.o \
	  ft_strlen.o \
	  ft_strnew.o \
	  ft_strrev.o \
	  ft_strsub.o

#all: $(NAME)

#$(NAME):
#	gcc -Wall -Werror -Wextra -c $(SRC) -I $(HEAD)
#	ar rc $(NAME) $(OBJ)
#	ranlib $(NAME)

#gg:
#	gcc $(SRC) main.c -I $(HEAD) -L. -lft

#clean:
#	make clean -C libft
#	rm -rf $(OBJ)

#fclean: clean
#	make fclean -C libft
#	rm -rf $(NAME)
#	rm -rf libft.a

#re: fclean all
