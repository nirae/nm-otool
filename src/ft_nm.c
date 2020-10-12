/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 12:02:40 by ndubouil          #+#    #+#             */
/*   Updated: 2020/10/12 15:15:10 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm-otool.h"

int is_macho(void *file)
{
    uint32_t magic;

    // Check if it's a macho file
    magic = *(uint32_t *)(file);
    if (magic != MH_MAGIC && magic != MH_CIGAM && magic != MH_MAGIC_64 && magic != MH_CIGAM_64)
    {
        ft_fd_printf(2, "Pas un macho");
        return (FALSE);
    }
    if (magic == MH_MAGIC_64 || magic == MH_CIGAM_64)
        ft_printf("64bit\n");
    else if (magic == MH_MAGIC || magic == MH_CIGAM)
        ft_printf("32bit\n");
    return (TRUE);
}

void    *get_file(char *filename)
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
    if ((file = mmap(NULL, file_stat.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
    {
        ft_fd_printf(2, "mmap failed");
        return (NULL);
    }
    return (file);
}

int ft_nm(char *filename)
{
    void                    *file;
    uint32_t                cmd_numbers;
    struct load_command     *lc;
    uint32_t section_numbers;
	void *section;

    if ((file = get_file(filename)) == NULL)
    {
        ft_fd_printf(2, "file == NULL");
        return (FALSE);
    }
    if (is_macho(file) == FALSE)
        return (FALSE);

    cmd_numbers = ((struct mach_header *)file)->ncmds;

    lc = (struct load_command *)(file + sizeof(struct mach_header));

    // Loop on load commands
    while (cmd_numbers)
    {
        if (lc->cmd == LC_SEGMENT)
        {
            struct segment_command *s = ((struct segment_command *)(lc));
            section = s + sizeof(struct segment_command);
        	section_numbers = ((struct segment_command *)(lc))->nsects;
            // Loop on sections
            while (section_numbers)
            {
                struct section *sec = ((struct section *)(section));
		        ft_printf("SECTION %s\n", sec->sectname);
		        section += sizeof(struct section);
                section_numbers--;
	        }

            ft_printf("SEGMENT %s\n", ((struct segment_command *)(lc))->segname);
        }
        // else if (lc->cmd == LC_SYMTAB)
        //     ft_printf("SYMTAB %s\n");
        lc = (void *)lc +lc->cmdsize;
        cmd_numbers--;
    }

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
