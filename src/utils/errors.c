/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 15:51:33 by ndubouil          #+#    #+#             */
/*   Updated: 2020/10/20 18:25:27 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm-otool.h"

int get_errors_64(void *file, void *lc)
{
    uint64_t size;
    void *end;

    size = ((struct segment_command_64 *)(lc))->cmdsize;
    struct mach_header_64 *header = ((struct mach_header_64 *)(file));
    end = ((struct segment_command_64 *)(lc)) + header->sizeofcmds;
    if ((void *)lc + size > end)
    {
        ft_printf("get_errors_64 corrupted\n");
        return (FALSE);
    }
    return (TRUE);
}

int get_errors_32(void *file, void *seg, int type)
{
    uint64_t size;
    void *end;
    struct segment_command *sc;
    
    sc = ((struct segment_command *)(seg));
    size = addr_32(sc->cmdsize, type);
    struct mach_header *header = ((struct mach_header *)(file));
    end = sc + addr_32(header->sizeofcmds, type);
    if ((void *)sc + size > end)
    {
        ft_printf("get_errors_32 corrupted\n");
        return (FALSE);
    }
    return (TRUE);
}

int get_overflow_64(void *file, void *addr, size_t file_size)
{
    if ((void *)addr > (file + file_size) || addr < file)
    {
        ft_printf("get_overflow_64 corrupted\n");
        return (FALSE);
    }
    return (TRUE);
}

int get_overflow_32(void *file, void *addr, size_t file_size)
{
    if ((void *)addr > (file + file_size) || addr < file)
    {
        ft_printf("get_overflow_32 corrupted\n");
        return (FALSE);
    }
    return (TRUE);
}
