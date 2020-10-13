/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 12:02:40 by ndubouil          #+#    #+#             */
/*   Updated: 2020/10/13 20:38:40 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm-otool.h"

int ft_nm(char *filename)
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

    load_commands_handler(file, type);

    return (TRUE);
}

int main(int ac, char **av)
{
    if (ac != 2)
    {
        ft_putendl("usage: ft_nm <file>");
        return (EXIT_FAILURE);
    }
    if (ft_nm(av[1]) == FALSE)
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}
