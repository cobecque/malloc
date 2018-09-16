# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cobecque <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/17 17:21:49 by cobecque          #+#    #+#              #
#    Updated: 2018/03/09 15:24:48 by cobecque         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

INC_NAME = ./../includes
SRC_NAME = ft_isascii.c\
		   ft_swap.c\
		   ft_foreach.c\
		   ft_range.c\
		   ft_abs.c\
		   ft_lstnew.c\
		   ft_lstdelone.c\
		   ft_lstdel.c\
		   ft_lstadd.c\
		   ft_iswhitespace.c\
		   ft_lstiter.c\
		   ft_lstmap.c\
		   ft_memchr.c\
		   ft_putnbr_fd.c\
		   ft_strcmp.c\
		   ft_striteri.c\
		   ft_strncat.c\
		   ft_strrchr.c\
		   ft_toupper.c\
		   ft_isdigit.c\
		   ft_memcmp.c\
		   ft_putchar.c\
		   ft_putstr.c\
		   ft_strcpy.c\
		   ft_strjoin.c\
		   ft_strncmp.c\
		   ft_strsplit.c\
		   ft_atoi.c\
		   ft_isprint.c\
		   ft_memcpy.c\
		   ft_putchar_fd.c\
		   ft_putstr_fd.c\
		   ft_strdel.c\
		   ft_strlcat.c\
		   ft_strncpy.c\
		   ft_strstr.c\
		   ft_bzero.c\
		   ft_itoa.c\
		   ft_memdel.c\
		   ft_putendl.c\
		   ft_strcat.c\
		   ft_strdup.c\
		   ft_strlen.c\
		   ft_strnequ.c\
		   ft_strsub.c\
		   ft_isalnum.c\
		   ft_memalloc.c\
		   ft_memmove.c\
		   ft_putendl_fd.c\
		   ft_strchr.c\
		   ft_strequ.c\
		   ft_long_itoa.c\
		   ft_strrev.c\
		   ft_strmap.c\
		   ft_strnew.c\
		   ft_strtrim.c\
		   ft_isalpha.c\
		   ft_memccpy.c\
		   ft_memset.c\
		   ft_putnbr.c\
		   ft_strclr.c\
		   ft_striter.c\
		   ft_strmapi.c\
		   ft_strnstr.c\
		   ft_tolower.c\
		   gnl/get_next_line.c

SRC_DIR = ./src
OBJ_DIR = ./src/printf/obj

SRC_PATH = $(addprefix $(SRC_DIR)/,$(SRC_NAME))
OBJ_PATH = $(addprefix $(OBJ_DIR)/,$(SRC_NAME:.c=.o))

CC = gcc
FLAGS = -Wall -Werror -Wextra

all :
	@mkdir -p ./src/printf/obj
	@mkdir -p ./src/printf/obj/gnl
	@$(MAKE) $(NAME)

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c
	@mkdir -p obj/gnl
	@$(CC) $(FLAGS) -I $(INC_NAME) -o $@ -c $<
	@printf $(C_BLU) "        [ ✔ ] $<"

$(NAME): $(OBJ_PATH)
	@ar -q $(NAME) $(OBJ_PATH) 2>/dev/null
	@printf $(C_CYA) "        [ ✔ ] compiled -> $(NAME)"

clean :
	@rm -rf $(OBJ_DIR)
	@rm -rf obj
	@/bin/rm -f $(OBJ_PATH)

fclean : clean
	@/bin/rm -f $(NAME)

re : fclean all

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

