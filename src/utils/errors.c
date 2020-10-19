/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 15:51:33 by ndubouil          #+#    #+#             */
/*   Updated: 2020/10/19 19:13:31 by ndubouil         ###   ########.fr       */
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

int get_errors_32(void *file, void *lc)
{
    uint64_t size;
    void *end;

    size = ((struct segment_command *)(lc))->cmdsize;
    struct mach_header *header = ((struct mach_header *)(file));
    end = ((struct segment_command *)(lc)) + header->sizeofcmds;
    if ((void *)lc + size > end)
    {
        ft_printf("get_errors_32 corrupted\n");
        return (FALSE);
    }
    return (TRUE);
}

int get_overflow_64(void *file, void *lc, void *addr, size_t file_size)
{
    void *end;

    struct mach_header_64 *header = ((struct mach_header_64 *)(file));
    end = ((struct segment_command_64 *)(lc)) + header->sizeofcmds;
    if ((void *)addr > (file + file_size) || addr > (void *)end || addr < file)
    {
        ft_printf("get_overflow_64 corrupted\n");
        return (FALSE);
    }
    return (TRUE);
}

int get_overflow_32(void *file, void *lc, void *addr, size_t file_size)
{
    void *end;

    struct mach_header *header = ((struct mach_header *)(file));
    end = ((struct segment_command *)(lc)) + header->sizeofcmds;
    if ((void *)addr > (file + file_size) || addr > (void *)end || addr < file)
    {
        ft_printf("get_overflow_32 corrupted\n");
        return (FALSE);
    }
    return (TRUE);
}
