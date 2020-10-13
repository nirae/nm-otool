/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 18:22:06 by ndubouil          #+#    #+#             */
/*   Updated: 2020/10/13 18:31:16 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm-otool.h"

int load_commands_handler(void *file, int type)
{
    uint32_t                cmd_numbers;
    struct load_command     *lc;

    if (type == BIT64)
    {
        cmd_numbers = ((struct mach_header_64 *)file)->ncmds;
        lc = (struct load_command *)(file + sizeof(struct mach_header_64));
    }
    else
    {
        cmd_numbers = ((struct mach_header *)file)->ncmds;
        lc = (struct load_command *)(file + sizeof(struct mach_header));
    }
    while (cmd_numbers--)
    {
        if (type == BIT64)
            segment_command_handler_64(file, lc);
        else
            segment_command_handler_32(file, lc);
        lc = (void *)lc +lc->cmdsize;
    }
    return (TRUE);
}
