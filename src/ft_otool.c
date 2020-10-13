/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 12:02:40 by ndubouil          #+#    #+#             */
/*   Updated: 2020/10/13 20:38:43 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm-otool.h"

int ft_otool(char *filename)
{
    void                    *file;
    int type;

    if ((file = get_file(filename)) == NULL)
    {
        ft_fd_printf(2, "file == NULL");
        return (FALSE);
    }
    if ((type = is_macho(file)) == FALSE)
        return (FALSE);
    ft_printf("%s:\n", filename);
    load_commands_handler(file, type);

    return (TRUE);
}

int main(int ac, char **av)
{
    if (ac != 2)
    {
        ft_putendl("usage: ft_otool <file>");
        return (EXIT_FAILURE);
    }
    if (ft_otool(av[1]) == FALSE)
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}
