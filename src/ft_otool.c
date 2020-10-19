/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 12:02:40 by ndubouil          #+#    #+#             */
/*   Updated: 2020/10/16 17:20:22 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm-otool.h"

int ft_otool(char *filename)
{
    void        *file;
    int         type;
    size_t      size;

    if ((file = get_file(filename, &size)) == NULL)
    {
        ft_fd_printf(2, "file == NULL");
        return (FALSE);
    }
    if ((type = is_macho(file)) == FALSE)
        return (FALSE);
    ft_printf("%s:\n", filename);
    handler(file, type, size);
    // load_commands_handler(file, type, size);
    munmap(file, size);
    return (TRUE);
}

int main(int ac, char **av)
{
    int     i;

    if (ac < 2)
    {
        ft_putendl("usage: ft_otool <file>");
        return (EXIT_FAILURE);
    }
    i = 1;
    while (av[i])
    {
        if (ft_otool(av[i]) == FALSE)
            return (EXIT_FAILURE);
        i++;    
    }
    return (EXIT_SUCCESS);
}