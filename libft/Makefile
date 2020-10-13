# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/13 09:16:22 by ndubouil          #+#    #+#              #
#    Updated: 2019/11/26 18:03:37 by ndubouil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include sources.mk
include headers.mk

# Binaries and Flags
CC		=	/usr/bin/gcc
AR		=	/usr/bin/ar
RANLIB	=	/usr/bin/ranlib
RM		=	/bin/rm
CFLAGS	=	-Wall -Wextra -Werror -g3

# Obj files
OBJ		=	$(patsubst %.c,%.o,$(SRCS))

# Library name
NAME	=	libft.a

.PHONY: all clean fclean re

all:		$(NAME)
			@true

$(NAME):	$(OBJ) $(HFILES) ft_printf Makefile
			@$(AR) rc $(NAME) $(OBJ)
			@$(RANLIB) $(NAME)
			@echo "Compiling ft_printf"
			@make -C ft_printf
			@mv ft_printf/libftprintf.a $(NAME)
			@echo "Building $(NAME)"
			@$(AR) rc $(NAME) $(OBJ)
			@$(RANLIB) $(NAME)
			@echo "The library $(NAME) is ready"

%.o:		%.c
			@echo "Creating $@ ..."
			@$(CC) $(CFLAGS) -c $< -o $@ -I include

clean:
			@echo "Cleaning libft Objs ..."
			@$(RM) -f $(OBJ)
			@make clean -C ft_printf

fclean: clean
			@echo "Cleaning $(NAME)"
			@$(RM) -f $(NAME)
			@make fclean -C ft_printf

re: fclean all
