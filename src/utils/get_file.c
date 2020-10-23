/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 20:37:56 by ndubouil          #+#    #+#             */
/*   Updated: 2020/10/23 18:01:31 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm-otool.h"

int    valid_macho(void *file)
{
    uint32_t magic;

    magic = *(uint32_t *)(file);
    if (magic != MH_MAGIC && magic != MH_CIGAM &&
        magic != MH_MAGIC_64 && magic != MH_CIGAM_64 &&
        magic != FAT_MAGIC && magic != FAT_CIGAM)
    {
        return (FALSE);
    }
    return (TRUE);
}

void    *get_file(char *filename, size_t *size, int *err)
{
    int fd;
    struct stat     file_stat;
    void    *file;

    *err = 0;
    // Open file
    if ((fd = open(filename, O_RDONLY)) < 0)
    {
        *err = OPEN_FAILED;
        return (NULL);
    }
    if (fstat(fd, &file_stat) < 0)
        return (NULL);
    if (file_stat.st_size == 0)
        return (NULL);
    file = mmap(NULL, file_stat.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    close(fd);
    if (file == MAP_FAILED)
        return (NULL);
    *size = file_stat.st_size;
    if (!valid_macho(file))
        return (NULL);
    return (file);
}
