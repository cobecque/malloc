# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mverdier <mverdier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/14 14:55:01 by mverdier          #+#    #+#              #
#    Updated: 2019/12/15 01:12:48 by rostroh          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors.

ORANGE =	\033[1;33m   #It is actually Yellow, but i changed yellow to orange.

GREEN =		\033[1;32m

RED =		\033[1;31m

RES =		\033[0m

#------------------------------------------------------------------------------#

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = 		libft_malloc_$(HOSTTYPE).so

SRCDIR =	./src

OBJDIR =	./obj

INCDIR =	./includes

# List all sources, objects and includes files of 'libft'.

SRC =		malloc.c realloc.c header.c write.c release_memory.c	\
			check_memory.c tiny.c show.c small.c large.c clear_area.c		\
			type.c creation.c read.c block.c get_size.c

INC =		malloc.h

SRCS =		$(SRC:%=$(SRCDIR)/%)

OBJS =		$(SRC:%.c=$(OBJDIR)/%.o)

INCS =		$(INC:%=$(INCDIR)/%)

LIBDIR =	./libft

LIBNAME =	libft.a

LIB =		$(LIBDIR)/$(LIBNAME)

#------------------------------------------------------------------------------#
# List all compilation variables.

CC =		gcc

CFLAGS =	-Wall			\
			-Wextra			\
			-Werror			\

INCFLAGS =	-I $(INCDIR)

LFLAGS =	-L $(LIBDIR) -l$(LIBNAME:lib%.a=%)

FLAGS =		$(CFLAGS)		\
			$(INCFLAGS)

#------------------------------------------------------------------------------#
# List all rules used to make libft.a

all:
	@$(MAKE) -C $(LIBDIR)
	@$(MAKE) $(NAME)

$(NAME): $(OBJS) $(LIB)
	@$(MAKE) printname
	@printf "%-15s%s\n" Linking $@
	@$(CC) $(CFLAGS) $^ -shared -o $@ $(LFLAGS)
	@ln -fs $(NAME) libft_malloc.so
	@printf "$(GREEN)"
	@echo "Compilation done !"
	@printf "$(RES)"

$(OBJS): $(INCS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	@$(MAKE) printname
	@printf "%-15s%s\n" Compiling $@
	@$(CC) $(FLAGS) -o $@ -c -fPIC $<

printname:
	@printf "$(ORANGE)"
	@printf "[%-15s " "$(NAME)]"
	@printf "$(RES)"

clean:
	@$(MAKE) printname
	@echo Suppressing obj files
	@printf "$(RED)"
	rm -rf $(OBJS)
	@rm -rf $(OBJDIR)
	@printf "$(RES)"

fclean: clean
	@make fclean -C $(LIBDIR)
	@$(MAKE) printname
	@echo Suppressing $(NAME)
	@printf "$(RED)"
	rm -rf $(NAME)
	rm -rf libft_malloc.so
	@printf "$(RES)"

re: fclean
	@$(MAKE) all

#------------------------------------------------------------------------------#
# List of all my optionnals but usefull rules.

NORM = `norminette $(SRCS) $(INCS) | grep -B1 Error | cat`

norm:
	@$(MAKE) printname
	@echo "Passage de la norminette :"
	@if [ "$(NORM)" == "`echo ""`" ];									\
		then															\
			echo "$(GREEN)Tous les fichiers sont a la norme !$(RES)";	\
		else															\
			echo "$(RED)$(NORM)$(RES)";									\
	fi

check:
	#@$(MAKE) -C $(LIBDIR) check
	@$(MAKE) norm

# A rule to make git add easier

git:
	@$(MAKE) -C $(LIBDIR) git
	@$(MAKE) printname
	@echo Adding files to git repository
	@printf "$(GREEN)"
	git add $(SRCS) $(INCS) Makefile
	@printf "$(RES)"
	git status

.PHONY: all clean re fclean git norm check
