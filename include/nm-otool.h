/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm-otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 15:21:51 by ndubouil          #+#    #+#             */
/*   Updated: 2020/10/13 20:38:31 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_OTOOL_H
# define NM_OTOOL_H

#include "libft.h"
#include "libftprintf.h"
#include "mach-o/loader.h"

#include <stdio.h>

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

#define BIT64 3
#define BIT32 4

/*
** hexdump.c
*/
int hexdump (void *start, int len, uint64_t addr);

/*
** segments.c
*/
int segment_command_handler_32(void *file, void *lc);
void segment_command_handler_64(void *file, void *lc);

/*
** load_commands.c
*/
int load_commands_handler(void *file, int type);

/*
** is_macho.c
*/
int is_macho(void *file);

/*
** get_file.c
*/
void    *get_file(char *filename);

# endif
