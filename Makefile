# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/02 11:57:24 by ndubouil          #+#    #+#              #
#    Updated: 2020/10/13 18:47:40 by ndubouil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include sources.mk
include headers.mk

# Binaries and Flags

CC		=	/usr/bin/gcc
RM		=	/bin/rm
CFLAGS	=	-Wall -Wextra -Werror -g3

# Directories

LIBFT	=	./libft/
ILIBFT	=	./$(LIBFT)include/
H		=	./include/
MACHOH	=	./macho-headers/

#  Files

OTOOL_SRCS = $(SRCS)
OTOOL_SRCS += src/ft_otool.c
NM_SRCS = $(SRCS)
NM_SRCS += src/ft_nm.c

OTOOL_OBJ		=	$(patsubst %.c,%.o,$(OTOOL_SRCS))
NM_OBJ		=	$(patsubst %.c,%.o,$(NM_SRCS))


.PHONY: all clean fclean re

# Rules

all:		ft_otool ft_nm
		@true

ft_otool:	Makefile $(OTOOL_OBJ) $(HFILES) $(LIBFT)
		@echo "Compiling Libft ..."
		@make -C $(LIBFT)
		@echo "Building ft_otool ..."
		@$(CC) $(CFLAGS) $(OTOOL_OBJ) -I$(H) -I$(MACHOH) -I$(ILIBFT) -L$(LIBFT) -lft -o ft_otool
		@echo "I'm READY"

ft_nm:	Makefile $(NM_OBJ) $(HFILES) $(LIBFT)
		@echo "Compiling Libft ..."
		@make -C $(LIBFT)
		@echo "Building ft_nm ..."
		@$(CC) $(CFLAGS) $(NM_OBJ) -I$(H) -I$(MACHOH) -I$(ILIBFT) -L$(LIBFT) -lft -o ft_nm
		@echo "I'm READY"

%.o:		%.c $(HFILES)
		@echo "Creating $@ ..."
		@$(CC) $(CFLAGS) -I$(H) -I$(MACHOH) -I$(ILIBFT) -c $< -o $@

clean:
		@echo "Cleaning Objs ..."
		@$(RM) -f $(OBJ)
		@echo "Cleaning Libft Objs ..."
		@make clean -C $(LIBFT)

fclean:		clean
		@echo "Cleaning $(NAME) exec"
		@$(RM) -f $(NAME)
		@echo "Cleaning libft exec"
		@make fclean -C $(LIBFT)

re:			fclean all
