/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 12:02:40 by ndubouil          #+#    #+#             */
/*   Updated: 2020/10/23 18:02:01 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm-otool.h"

char    *ft_nm(char *filename)
{
    void        *file;
    int         type;
    size_t      size;
    int         err;
    // int         ret;

    if (!(file = get_file(filename, &size, &err)))
    {
        if (err == OPEN_FAILED)
            return ("No such file or directory");
        return ("The file was not recognized as a valid object file");
    }
    if ((type = get_macho_type(file, NM)) == FALSE)
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
            ft_fd_printf(2, "ft_nm: error: %s: File name too long\n", tab[i]);
            continue;
        }
        if ((err = ft_nm(tab[i])))
        {
            ft_fd_printf(2, "ft_nm: error: %s: %s\n", tab[i], err);
            return (FALSE);
        }
        i++;
    }
    return (TRUE);
}

int     main(int ac, char **av)
{
    char    filename[FILENAME_MAX_SIZE];
    // char    **tab;

    ft_bzero(filename, sizeof(filename));
    // tab = av;
    if (ac < 2)
    {
        ft_strcpy(filename, "a.out");
        av[0] = filename;
        av[1] = 0;
        if (!entry(av))
            return (EXIT_FAILURE);
    }
    else
    {
        if (!entry(&av[1]))
            return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}
