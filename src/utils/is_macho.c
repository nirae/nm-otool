/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_macho.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 20:36:43 by ndubouil          #+#    #+#             */
/*   Updated: 2020/10/16 17:18:33 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm-otool.h"

int get_macho_type(uint32_t magic)
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
    return (type);
}

// int get_endianess(void *file, int type)
// {
//     uint32_t magic;

//     magic = *(uint32_t *)(file);
//     if (type == BIT64)
//     {

//     }
//     else if (type == BIT32)
//     {

//     }
//     else 
//     if (magic == MH_MAGIC_64 || magic == MH_CIGAM_64)
//         return (BIT64);
//     else if (magic == MH_MAGIC || magic == MH_CIGAM)
//         return (BIT32);
//     else if (magic == FAT_MAGIC || magic == FAT_CIGAM)
//         return (FAT);
// }

int is_macho(void *file)
{
    uint32_t magic;

    magic = *(uint32_t *)(file);
    if (magic != MH_MAGIC && magic != MH_CIGAM &&
        magic != MH_MAGIC_64 && magic != MH_CIGAM_64 &&
        magic != FAT_MAGIC && magic != FAT_CIGAM)
    {
        ft_fd_printf(2, "Pas un macho");
        return (FALSE);
    }
    return (get_macho_type(magic));
}
