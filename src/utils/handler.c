/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 17:19:28 by ndubouil          #+#    #+#             */
/*   Updated: 2020/10/23 17:29:05 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm-otool.h"

int     handler(void *file, int type, size_t size)
{
    if (type & FAT)
        return (fat_handler(file, type, size));
    return (object_handler(file, type, size));
}
