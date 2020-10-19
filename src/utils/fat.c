/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 17:37:34 by ndubouil          #+#    #+#             */
/*   Updated: 2020/10/19 15:58:21 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm-otool.h"

static int manage_fat(void *file, int t, void *arch)
{
    int         type;

    struct fat_arch *a = ((struct fat_arch *)(arch));
    if (t & L_ENDIAN)
    {
        if (uint32_swap(a->cputype) == CPU_TYPE_X86_64)
            printf("x86\n");
        if ((type = is_macho(file + uint32_swap(a->offset))) == FALSE)
            return (FALSE);
        object_handler(file + uint32_swap(a->offset), type, uint32_swap(a->size));
    }
    else
    {
        if (a->cputype == CPU_TYPE_X86_64)
            printf("x86\n");
        if ((type = is_macho(file + a->offset)) == FALSE)
            return (FALSE);
        object_handler(file + a->offset, type, a->size);
    }
	return (TRUE);
}

int fat_handler(void *file, int type)
{
	struct fat_arch		*arch;
	uint32_t	        numbers_arch;
    uint32_t                 i;
	// arch = ((struct fat_header *)(file))->nfat_arch;
	arch = file + sizeof(struct fat_header);
    
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
        if (manage_fat(file, type, arch) == FALSE)
        {
            return (FALSE);
        }
	    arch = (void *)arch + sizeof(struct fat_arch);   
        i++;
    }
	return (TRUE);
}
