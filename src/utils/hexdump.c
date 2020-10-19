/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexdump.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 18:19:58 by ndubouil          #+#    #+#             */
/*   Updated: 2020/10/19 16:25:58 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm-otool.h"

static int	ft_count_base(unsigned long long int n)
{
	int		i;

	i = 0;
	while (n != 0)
	{
		n = n / 16;
		i++;
	}
	return (i);
}

void hex_to_str(uint64_t addr, char *result, int size)
{
    int		len;
    char    base_str[16];

    ft_strncpy(base_str, "0123456789abcdef", 16);
	len = ft_count_base(addr);
    ft_memset(result, 0, size);
    result[0] = '0';
    result[1] = '0';
	while (addr != 0)
	{
		result[--len] = base_str[addr % 16];
		addr = addr / 16;
	}
}

int hexdump (void *start, int len, uint64_t addr)
{
    int i;
    // char buff[17];
    unsigned char *c = (unsigned char *)start;
    char str_addr[11];
    char tab[3];

    if (len <= 0)
        return (FALSE);

    i = 0;
    while (i < len)
    {
        // Multiple of 16 means new line (with line offset).
        if ((i % 16) == 0) {
            // Don't print ASCII buffer for the "zeroth" line.
            if (i != 0)
            {
                // ft_putstr("  ");
                // ft_printf("  %s\n", buff);
                ft_printf("\n");
                // ft_putendl(buff);
            }
            // Output the address
            // ft_printf ("000000%lx ", (uint64_t)addr + i);
            // str = ft_ulli_itoa_base((uint64_t)addr + i, "0123456789abcdef");
            hex_to_str((uint64_t)addr + i, str_addr, sizeof(str_addr));
            ft_printf("000000%s\t", str_addr);
        }
        else
        {
            ft_printf(" ");
        }
        
        // Now the hex code for the specific character.

        // ft_printf(" %s", ft_ulli_itoa_base((uint64_t)c[i], "0123456789abcdef"));
        hex_to_str((uint64_t)c[i], tab, sizeof(tab));
        ft_printf("%s", tab);
        // ft_printf(" %02llx", c[i]);
        // And buffer a printable ASCII character for later.
        // if (!ft_isprint(c[i]))
        //     buff[i % 16] = '.';
        // else
        //     buff[i % 16] = c[i];
        // buff[(i % 16) + 1] = '\0';
        i++;
    }
    // Pad out last line if not exactly 16 characters.
    // while ((i % 16) != 0) {
    //     ft_printf("   ");
    //     i++;
    // }
    // // And print the final ASCII buffer.
    // ft_printf("  %s\n", buff);
    ft_printf("\n");
    return (TRUE);
}
