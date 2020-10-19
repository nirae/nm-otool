/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 17:19:28 by ndubouil          #+#    #+#             */
/*   Updated: 2020/10/19 15:58:58 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm-otool.h"

int     handler(void *file, int type, size_t size)
{
    if (type & FAT)
        return (fat_handler(file, type));
    else if (type & BIT64 || type & BIT32)
        return (object_handler(file, type, size));
    else
        return (FALSE);
    return (TRUE);
}
