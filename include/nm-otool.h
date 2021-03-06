/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm-otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 15:21:51 by ndubouil          #+#    #+#             */
/*   Updated: 2020/10/23 18:01:42 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_OTOOL_H
# define NM_OTOOL_H

#include "libft.h"
#include "libftprintf.h"
#include "mach-o/loader.h"
#include "mach-o/nlist.h"
#include "mach-o/fat.h"

#include <stdio.h>

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

#define FILENAME_MAX_SIZE 255

#define OPEN_FAILED 100

#define BIT64   1
#define BIT32   2
#define FAT     0x10
#define L_ENDIAN 0x100
#define NM 0x1000
#define OTOOL 0x2000

/*
 * from https://github.com/opensource-apple/cctools/blob/master/include/stuff/arch.h
 * The structure describing an architecture flag with the string of the flag
 * name, and the cputype and cpusubtype.
 */
typedef struct	s_arch_flag {
	char			*name;
	cpu_type_t		cputype;
	cpu_subtype_t	cpusubtype;
}				t_arch_flag;

/*
** errors.c
*/
int get_errors_64(void *file, void *lc);
int get_errors_32(void *file, void *lc, int type);
int get_overflow_64(void *file, void *addr, size_t file_size);
int get_overflow_32(void *file, void *addr, size_t file_size);


/*
** hexdump.c
*/
void hex_to_str(uint64_t addr, char *result, int size);
int hexdump(void *start, int len, uint64_t addr, int type);

/*
** segments.c
*/
int segment_command_handler_32(void *file, void *lc, int type, size_t file_size);
int segment_command_handler_32_nm(void *file, void *lc, int type, size_t file_size);
// int get_sections_32_nm(void *file, void *lc, int type, size_t file_size, t_list **sections);
int segment_command_handler_64(void *file, void *lc, size_t file_size);
int segment_command_handler_64_nm(void *file, void *lc, size_t file_size);
// int get_sections_64_nm(void *file, void *lc, size_t file_size, t_list **sections);

/*
** handler.c
*/
int     handler(void *file, int type, size_t size);


/*
** object.c
*/
int object_handler(void *file, int type, size_t size);

/*
** fat.c
*/
int fat_handler(void *file, int type, size_t size);


/*
** is_macho.c
*/
int get_macho_type(void *file, int bin);

/*
** get_file.c
*/
void    *get_file(char *filename, size_t *size, int *err);
int     valid_macho(void *file);

/*
** endianess.c
*/
uint32_t	uint32_swap(uint32_t nb);
uint32_t    addr_32(uint32_t nb, int type);
// struct segment_command *swap_segment_command(struct segment_command *base);


# endif
