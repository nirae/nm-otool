/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexdump.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 18:19:58 by ndubouil          #+#    #+#             */
/*   Updated: 2020/10/19 18:27:07 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm-otool.h"

// static int	ft_count_base(unsigned long long int n)
// {
// 	int		i;

// 	i = 0;
// 	while (n != 0)
// 	{
// 		n = n / 16;
// 		i++;
// 	}
// 	return (i);
// }

void hex_to_str(uint64_t addr, char *result, int size)
{
    int		len;
    char    base_str[16];

    ft_strncpy(base_str, "0123456789abcdef", 16);
	// len = ft_count_base(addr);
	len = size - 1;
    ft_memset(result, '0', size);
    result[size - 1] = 0;
    // ft_memset(result, 0, size);
    // result[0] = '0';
    // result[1] = '0';
	while (addr != 0)
	{
		result[--len] = base_str[addr % 16];
		addr = addr / 16;
	}
}

int hexdump (void *start, int len, uint64_t addr, int type)
{
    int i;
    unsigned char *c = (unsigned char *)start;
    char str_addr[17];
    // char tab[3];

    if (len <= 0)
        return (FALSE);

    i = 0;
    while (i < len)
    {
        // Multiple of 16 means new line (with line offset).
        if ((i % 16) == 0) {
            if (i != 0)
                ft_printf("\n");
            if (type == BIT64)
                hex_to_str((uint64_t)addr + i, str_addr, sizeof(str_addr));
            else
                hex_to_str((uint64_t)addr + i, str_addr, 9);
            ft_printf("%s\t", str_addr);
        }
        hex_to_str((uint64_t)c[i], str_addr, 3);
        ft_printf("%s ", str_addr);
        i++;
    }
    ft_printf("\n");
    return (TRUE);
}
