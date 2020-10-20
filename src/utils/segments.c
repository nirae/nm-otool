/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segments.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 18:21:43 by ndubouil          #+#    #+#             */
/*   Updated: 2020/10/20 15:52:30 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm-otool.h"

int segment_command_handler_64(void *file, void *lc, size_t file_size)
{
    uint32_t        section_numbers;
	void            *section;

    if (get_errors_64(file, lc) == FALSE)
        return (FALSE);
    struct segment_command_64 *seg = ((struct segment_command_64 *)(lc));
    if (seg->cmd == LC_SEGMENT_64)
    {
        if (get_overflow_64(file, file + seg->fileoff + seg->filesize, file_size) == FALSE)
            return (FALSE);
        // ft_printf("SEGMENT %s\n", ((struct segment_command_64 *)(lc))->segname);
        section = lc + sizeof(struct segment_command_64);
    	section_numbers = ((struct segment_command_64 *)(lc))->nsects;
        // Loop on sections
        while (section_numbers)
        {
            struct section_64 *sec = ((struct section_64 *)(section));
	        // ft_printf("SECTION %s\n", sec->sectname);
            if (get_overflow_64(file, file + sec->offset + sec->size, file_size) == FALSE)
                return (FALSE);
            if (ft_strcmp(sec->sectname, SECT_TEXT) == 0)
            {
                ft_printf("Contents of (%s,%s) section\n", sec->segname, sec->sectname);
                hexdump(file + sec->offset, sec->size, sec->addr, BIT64);
            }

	        section += sizeof(struct section_64);
            section_numbers--;
	    }
    }
    return (TRUE);
}

int segment_command_handler_32(void *file, void *lc, size_t file_size)
{
    uint32_t        section_numbers;
	void            *section;

    if (get_errors_32(file, lc) == FALSE)
        return (FALSE);
    struct segment_command *seg = ((struct segment_command *)(lc));
    if (seg->cmd == LC_SEGMENT)
    {
        if (get_overflow_32(file, file + seg->fileoff + seg->filesize, file_size) == FALSE)
            return (FALSE);
        section = lc + sizeof(struct segment_command);
    	section_numbers = ((struct segment_command *)(lc))->nsects;
        // Loop on sections
        while (section_numbers)
        {
            struct section *sec = ((struct section *)(section));
	        // ft_printf("SECTION %s\n", sec->sectname);
            if (get_overflow_32(file, file + sec->offset + sec->size, file_size) == FALSE)
                return (FALSE);
            if (ft_strcmp(sec->sectname, SECT_TEXT) == 0)
            {
                ft_printf("Contents of (%s,%s) section\n", sec->segname, sec->sectname);
                hexdump(file + sec->offset, sec->size, sec->addr, BIT32);
            }

	        section += sizeof(struct section);
            section_numbers--;
	    }
    }
    return (TRUE);
}
