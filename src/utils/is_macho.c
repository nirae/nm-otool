/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_macho.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 20:36:43 by ndubouil          #+#    #+#             */
/*   Updated: 2020/10/21 14:51:24 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm-otool.h"

int get_macho_type(uint32_t magic, int bin)
{
    int             type;

    type = 0;
    if (magic == MH_MAGIC_64 || magic == MH_CIGAM_64)
    {
        type += BIT64;
        if (magic == MH_CIGAM_64)
            type += L_ENDIAN;
    }
    else if (magic == MH_MAGIC || magic == MH_CIGAM)
    {
        type += BIT32;
        if (magic == MH_CIGAM)
            type += L_ENDIAN;
    }
    else if (magic == FAT_MAGIC || magic == FAT_CIGAM)
    {
        type += FAT;
        if (magic == FAT_CIGAM)
            type += L_ENDIAN;
        
    }
    if (bin == NM)
        type += NM;
    return (type);
}

int is_macho(void *file, int bin)
{
    uint32_t magic;

    magic = *(uint32_t *)(file);
    if (magic != MH_MAGIC && magic != MH_CIGAM &&
        magic != MH_MAGIC_64 && magic != MH_CIGAM_64 &&
        magic != FAT_MAGIC && magic != FAT_CIGAM)
    {
        ft_printf("Pas un macho");
        return (FALSE);
    }
    return (get_macho_type(magic, bin));
}
