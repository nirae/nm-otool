/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_macho.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 20:36:43 by ndubouil          #+#    #+#             */
/*   Updated: 2020/10/13 20:36:52 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm-otool.h"

int is_macho(void *file)
{
    uint32_t magic;

    // Check if it's a macho file
    magic = *(uint32_t *)(file);
    if (magic != MH_MAGIC && magic != MH_CIGAM &&
        magic != MH_MAGIC_64 && magic != MH_CIGAM_64)
    {
        ft_fd_printf(2, "Pas un macho");
        return (FALSE);
    }
    if (magic == MH_MAGIC_64 || magic == MH_CIGAM_64)
        return (BIT64);
    else if (magic == MH_MAGIC || magic == MH_CIGAM)
        return (BIT32);
    return (FALSE);
}
