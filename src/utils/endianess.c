/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   endianess.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 17:38:42 by ndubouil          #+#    #+#             */
/*   Updated: 2020/10/20 18:15:42 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm-otool.h"

uint32_t	uint32_swap(uint32_t nb)
{
	nb = ((nb << 8) & 0xFF00FF00) | ((nb >> 8) & 0xFF00FF);
	return ((nb << 16) | (nb >> 16));
}

uint32_t    addr_32(uint32_t nb, int type)
{
    if (type & L_ENDIAN)
	    return (uint32_swap(nb));
    return (nb);
}

// struct segment_command *swap_segment_command(struct segment_command *base)
// {
//     struct segment_command *seg;

//     seg = base;
//     seg->cmd = uint32_swap(base->cmd);
//     seg->cmdsize = uint32_swap(base->cmdsize);
//     ft_strncpy(seg->segname, base->segname, sizeof(base->segname));
//     seg->vmaddr = uint32_swap(base->vmaddr);
//     seg->vmsize = uint32_swap(base->vmsize);
//     seg->fileoff = uint32_swap(base->fileoff);
//     seg->filesize = uint32_swap(base->filesize);
//     seg->maxprot = base->maxprot;
//     seg->initprot = base->initprot;
//     seg->nsects = uint32_swap(base->nsects);
//     seg->flags = uint32_swap(base->flags);
//     return (seg);
// }
