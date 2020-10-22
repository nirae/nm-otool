/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 17:31:00 by ndubouil          #+#    #+#             */
/*   Updated: 2020/10/22 16:59:35 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm-otool.h"

int object_handler(void *file, int type, size_t size)
{
    uint32_t                cmd_numbers;
    struct load_command     *lc;
    int                     ret;

    if (type & BIT64)
    {
        cmd_numbers = ((struct mach_header_64 *)file)->ncmds;
        lc = (struct load_command *)(file + sizeof(struct mach_header_64));
    }
    else if (type & BIT32)
    {
        cmd_numbers = ((struct mach_header *)file)->ncmds;
        lc = (struct load_command *)(file + sizeof(struct mach_header));
    }
    else
    {
        return (FALSE);
    }
    while (cmd_numbers--)
    {
        if ((type & BIT64) && (lc->cmdsize % 8))
            return (FALSE);
        if (type & NM)
        {
            if (type & BIT64)
            {
                ret = segment_command_handler_64_nm(file, lc, size);
            }
            else
                ret = segment_command_handler_32_nm(file, lc, type, size);
        }
        else
        {
            if (type & BIT64)
                ret = segment_command_handler_64(file, lc, size);
            else
                ret = segment_command_handler_32(file, lc, type, size);
        }
        if (ret == FALSE)
            return (FALSE);
        if (type & BIT32)
            lc = (void *)lc + addr_32(lc->cmdsize, type);
        else
            lc = (void *)lc + lc->cmdsize;
    }
    return (TRUE);
}
