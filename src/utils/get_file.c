/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 20:37:56 by ndubouil          #+#    #+#             */
/*   Updated: 2020/10/20 14:53:23 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm-otool.h"

void    *get_file(char *filename, size_t *size)
{
    int fd;
    struct stat     file_stat;
    void    *file;

    // Open file
    if ((fd = open(filename, O_RDONLY)) < 0)
    {
        ft_fd_printf(2, "open failed");
        return (NULL);
    }
    if (fstat(fd, &file_stat) < 0)
    {
        ft_fd_printf(2, "fstat failed");
        return (NULL);
    }
    if (file_stat.st_size == 0)
    {
        ft_fd_printf(2, "fichier vide");
        return (NULL);
    }
    file = mmap(NULL, file_stat.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    close(fd);
    if (file == MAP_FAILED)
    {
        ft_fd_printf(2, "mmap failed");
        return (NULL);
    }
    *size = file_stat.st_size;
    return (file);
}
