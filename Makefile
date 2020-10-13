# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/02 11:57:24 by ndubouil          #+#    #+#              #
#    Updated: 2020/10/13 13:04:15 by ndubouil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include sources.mk
include headers.mk

# Binaries and Flags

CC		=	/usr/bin/gcc
RM		=	/bin/rm
CFLAGS	=	-Wall -Wextra -Werror -g

# Directories

LIBFT	=	./libft/
ILIBFT	=	./$(LIBFT)include/
H		=	./include/
MACHOH	=	./macho-headers/

#  Files

OBJ		=	$(patsubst %.c,%.o,$(SRCS))

# Name of the project

NAME	=	ft_nm

.PHONY: all clean fclean re

# Rules

all:		$(NAME)
		@true

$(NAME):	Makefile $(OBJ) $(MAIN) $(HFILES) $(LIBFT)
		@echo "Compiling Libft ..."
		@make -C $(LIBFT)
		@echo "Building $(NAME) ..."
		@$(CC) $(CFLAGS) $(OBJ) -I$(H) -I$(MACHOH) -I$(ILIBFT) -L$(LIBFT) -lft -o $(NAME)
		@echo "I'm READY"

%.o:		%.c $(HFILES)
		@echo "Creating $@ ..."
		@$(CC) $(CFLAGS) -I$(H) -I$(MACHOH) -I$(ILIBFT) -L$(LIBFT) -lft -c $< -o $@

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
