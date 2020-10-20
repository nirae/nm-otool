/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 17:37:34 by ndubouil          #+#    #+#             */
/*   Updated: 2020/10/20 19:22:22 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm-otool.h"

static int manage_fat(void *file, int t, void *arch)
{
    int         type;

    struct fat_arch *a = ((struct fat_arch *)(arch));
    if ((type = is_macho(file + addr_32(a->offset, t))) == FALSE)
        return (FALSE);
    object_handler(file + addr_32(a->offset, t), type, addr_32(a->size, t));
	return (TRUE);
}

static int is_our_cpu(int type, void *arch)
{
    struct fat_arch *a = ((struct fat_arch *)(arch));

    if (addr_32(a->cputype, type) == CPU_TYPE_X86_64)
    {
        return (TRUE);
    }
	return (FALSE);
}

int fat_handler(void *file, int type)
{
	struct fat_arch		*arch;
	uint32_t	        numbers_arch;
    uint32_t                 i;
    int                 x86;
	// arch = ((struct fat_header *)(file))->nfat_arch;
	arch = file + sizeof(struct fat_header);
    x86 = FALSE;
    if (type & L_ENDIAN)
    {
        numbers_arch = uint32_swap(((struct fat_header *)(file))->nfat_arch);
    }
    else
    {
        numbers_arch = ((struct fat_header *)(file))->nfat_arch;
    }
    i = 0;
    while (i < numbers_arch)
	{
        if (is_our_cpu(type, arch))
        {
            x86 = TRUE;
        }
	    arch = (void *)arch + sizeof(struct fat_arch);   
        i++;
    }
	arch = file + sizeof(struct fat_header);
    i = 0;
    while (i < numbers_arch)
	{
        if (addr_32(((struct fat_arch *)(arch))->cputype, type) != CPU_TYPE_X86_64 && x86)
        {
	        arch = (void *)arch + sizeof(struct fat_arch);   
            i++;
            continue;
        }
        if (manage_fat(file, type, arch) == FALSE)
        {
            return (FALSE);
        }
        if (x86)
        {
            break;
        }
	    arch = (void *)arch + sizeof(struct fat_arch);   
        i++;
    }
	return (TRUE);
}
