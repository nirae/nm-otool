/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 12:02:40 by ndubouil          #+#    #+#             */
/*   Updated: 2020/10/23 17:58:31 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm-otool.h"

char    *ft_otool(char *filename)
{
    void        *file;
    int         type;
    size_t      size;
    // int         ret;

    if (!(file = get_file(filename, &size)))
    {
        if (file == (void *)OPEN_FAILED)
            return ("No such file or directory");
        return ("The file was not recognized as a valid object file");
    }
    if ((type = get_macho_type(file, OTOOL)) == FALSE)
        return (FALSE);
    // ret = handler(file, type, size);
    handler(file, type, size);
    munmap(file, size);
    // return (ret);
    return (NULL);
}

int     entry(char **tab)
{
    int     i;
    char    *err;

    i = 0;
    while (tab[i])
    {
        if (ft_strlen(tab[i]) > FILENAME_MAX_SIZE)
        {
            ft_fd_printf(2, "ft_otool: error: %s: File name too long\n", tab[i]);
            continue;
        }
        if ((err = ft_otool(tab[i])))
        {
            ft_fd_printf(2, "ft_otool: error: %s: %s\n", tab[i], err);
            return (FALSE);
        }
        i++;
    }
    return (TRUE);
}

int     main(int ac, char **av)
{
    char    filename[FILENAME_MAX_SIZE];
    char    **tab;

    ft_bzero(filename, sizeof(filename));
    tab = av;
    if (ac < 2)
    {
        ft_strcpy(filename, "a.out");
        tab[0] = filename;
        tab[1] = 0; 
    }
    if (!entry(tab))
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}
