/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_macho_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 20:36:43 by ndubouil          #+#    #+#             */
/*   Updated: 2020/10/23 17:27:28 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm-otool.h"

int get_macho_type(void *file, int bin)
{
    int             type;
    uint32_t        magic;

    type = 0;
    magic = *(uint32_t *)(file);
    if (!valid_macho(file))
        return (FALSE);
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
