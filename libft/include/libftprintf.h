/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 15:08:59 by ndubouil          #+#    #+#             */
/*   Updated: 2020/10/13 19:18:49 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include "libft.h"
# include <stdarg.h>

/*
** If we are on Linux
*/

# ifdef __linux__
#  include <stdint.h>
# endif

/*
** MACROS for struct t_envp
*/

# define FALSE			0
# define TRUE			1
# define RIGHT			2
# define LEFT			3

# define BUFFER_SIZE	4096

# define FAIL			-666
# define MALLOC_FAIL	-999

/*
**		H =	4
**		HH = 5
**		L =	6
**		LL = 7
**		J =	8
**		Z =	9
*/

typedef enum					e_size
{
	H = 4,
	HH,
	L,
	LL,
	J,
	Z
}								t_size;

/*
**	Union for store the argument
*/

typedef union					u_types
{
	char						c;
	char						*str;
	wchar_t						*wstr;
	int							i;
	long int					li;
	long long int				lli;
	unsigned long long int		ulli;
	short int					si;
}								t_types;

/*
**	Structure for store the flags
*/

typedef struct					s_flags
{
	int							align;
	int							sign;
	int							zero;
	int							space;
	int							hash;
	long long int				width;
	long long int				precision;
	char						size;
	char						type;
}								t_flags;

/*
**	Structure for the buffer
*/

typedef	struct					s_buffer
{
	int							fd;
	int							len;
	int							pos_last_conv;
	char						buff[BUFFER_SIZE];
}								t_buffer;

/*
**	Environnement structure
*/

typedef struct					s_envp
{
	t_types						types;
	t_buffer					buff;
	int							len;
	int							pos;
	va_list						va;
	t_flags						flags;
}								t_envp;

/*
** Parsing (parser/...)
*/

int								parser(char *str, t_envp *env);
int								is_valid_flags(char c);
int								is_valid_sizeflag(char c);
int								is_valid_type(char c);
void							init_flags(t_envp *env);
int								set_flags(char *str, t_envp *env);
int								set_size(char *str, t_envp *env);
int								set_type(char *str, t_envp *env);
int								set_width(char *str, t_envp *env);
int								set_precision(char *str, t_envp *env);

/*
** Printing (printer/...)
*/

int								printer(t_envp *env);
int								print_char(t_envp *env);
int								print_big_char(t_envp *env);
int								print_string(t_envp *env);
int								print_big_string(t_envp *env);
int								print_address(t_envp *env);
int								print_percent(t_envp *env);
int								print_number(t_envp *env);
int								print_unsigned_number(t_envp *env);
int								print_octal(t_envp *env);
int								print_hexa(t_envp *env);

/*
**	Tools for hexa printer (printer/hexa_tools.c)
*/

int								print_width_right_hexa(t_envp *env, int len,
									char c);
int								print_width_left_hexa(t_envp *env, int len,
									char c);
void							print_prefix(t_envp *env);

/*
**	Tools for unicode (printer/unicode_tools/..)
*/

int								get_big_char(t_envp *env, int c
									, char result[5]);
int								ft_bigcharlen(int i);
int								ft_wstrlen(wchar_t *str);
int								ft_bigstrlen(wchar_t *str);

/*
** Buffer (buffer/buffer.c)
*/

int								putstr_in_buffer(t_buffer *buff, char *str);
int								putchar_in_buffer(t_buffer *buff, char c);
void							print_buffer(t_buffer *buff);
void							delete_end_of_buffer(t_buffer *buff, int start);

/*
**	THE FT_PRINTF !!!
*/

int								ft_fd_printf(int fd, const char *str, ...);
int								ft_printf(const char *str, ...);

#endif
