/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segments.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 18:21:43 by ndubouil          #+#    #+#             */
/*   Updated: 2020/10/22 19:08:52 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm-otool.h"

int get_section_64(void *file, uint8_t nb, size_t file_size)
{
    uint32_t        section_numbers;
	void            *section;
    void     *lc;
    uint8_t i = 1;

    lc = file + sizeof(struct mach_header_64);
    uint32_t cmd_numbers = ((struct mach_header_64 *)file)->ncmds;

    while (cmd_numbers--)
    {
        struct segment_command_64 *seg = (struct segment_command_64 *)lc;
        if (seg->cmd == LC_SEGMENT_64)
        {
            if (get_overflow_64(file, file + seg->fileoff + seg->filesize, file_size) == FALSE)
                return (FALSE);
            section = lc + sizeof(struct segment_command_64);
            section_numbers = ((struct segment_command_64 *)(lc))->nsects;
            // Loop on sections
            while (section_numbers)
            {
                struct section_64 *sec = ((struct section_64 *)(section));
                if (i == nb)
                {
                    if (ft_strcmp(sec->sectname, SECT_TEXT) == 0)
                        return ('T');
                    else if (ft_strcmp(sec->sectname, SECT_DATA) == 0)
                        return ('D');
                    else if (ft_strcmp(sec->sectname, SECT_BSS) == 0)
                        return ('B');
                    else
                        return ('S');   
                }
                    // ft_printf("GOOD %s, %s\n", sec->segname, sec->sectname);
                section += sizeof(struct section_64);
                section_numbers--;
                i++;
            }
        }
        lc = (void *)lc + ((struct load_command *)(lc))->cmdsize;
    }
    return (TRUE);
}

char get_symbol_letter_64(struct nlist_64 *symtab, void *file, size_t file_size)
{
    if ((N_TYPE & symtab->n_type) == N_UNDF)
    {
        // if (sym->name_not_found)
        //     return 'C';
        if (symtab->n_type & N_EXT)
            return 'U';
        else
            return '?';
    }
    else if ((N_TYPE & symtab->n_type) == N_SECT)
    {
        char c = get_section_64(file, symtab->n_sect, file_size);
        if (!(symtab->n_type & N_EXT))
            c -= 'A' - 'a';
        return c;
    }
    else if ((N_TYPE & symtab->n_type) == N_ABS)
    {
        return 'A';
    }
    else if ((N_TYPE & symtab->n_type) == N_INDR)
    {
        return 'I';
    }
    return ' ';
}

int segment_command_handler_64_nm(void *file, void *lc, size_t file_size)
{
    uint32_t        sym_numbers;
    uint32_t        i;
	// void            *section;
    char            tmp[17];

    i = 0;
    struct segment_command_64 *seg = ((struct segment_command_64 *)(lc));
    // ft_printf("debut: %s\n", seg->segname);
    if (get_errors_64(file, lc) == FALSE)
        return (FALSE);
    if (seg->cmd == LC_SYMTAB)
    {
        struct symtab_command *sym = ((struct symtab_command *)(lc));
        void *strtab = file + sym->stroff;
        void *symtab = file + sym->symoff;
        sym_numbers = sym->nsyms;
        while (sym_numbers)
        {
            ft_bzero(tmp, sizeof(tmp));
            struct nlist_64 *sym_data = ((struct nlist_64 *)(symtab));
            if (!get_overflow_64(file, sym_data, file_size))
                return (FALSE);
            char *name = strtab + sym_data->n_un.n_strx;
            if (N_STAB & sym_data->n_type)
            {
                symtab += sizeof(struct nlist_64);
                sym_numbers--;
                i++;
                continue;
            }
            if (sym_data->n_value)
                hex_to_str(sym_data->n_value, tmp, sizeof(tmp));
            else
                ft_memset(tmp, ' ', sizeof(tmp) - 1);
            // get_section_64(file, sym_data->n_sect, file_size);
            ft_printf("%s %c %s\n", tmp, get_symbol_letter_64(sym_data, file, file_size), name);
            symtab += sizeof(struct nlist_64);
            sym_numbers--;
            i++;
        }
    }
    return (TRUE);
}

int segment_command_handler_32_nm(void *file, void *lc, int type, size_t file_size)
{
    uint32_t        section_numbers;
	void            *section;
    struct segment_command *seg;

    seg = ((struct segment_command *)(lc));
    if (get_errors_32(file, seg, type) == FALSE)
        return (FALSE);
    if (addr_32(seg->cmd, type) == LC_SEGMENT)
    {
        ft_printf("NM");
        if (get_overflow_32(file, file + addr_32(seg->fileoff, type) + addr_32(seg->filesize, type), file_size) == FALSE)
            return (FALSE);
        section = lc + sizeof(struct segment_command);
    	section_numbers = addr_32(((struct segment_command *)(lc))->nsects, type);
        // Loop on sections
        while (section_numbers)
        {
            struct section *sec = ((struct section *)(section));
	        // ft_printf("SECTION %s\n", sec->sectname);
            if (ft_strcmp(sec->sectname, SECT_TEXT) == 0)
            {
                if (get_overflow_32(file, file + addr_32(sec->offset, type) + addr_32(sec->size, type), file_size) == FALSE)
                return (FALSE);
                ft_printf("Contents of (%s,%s) section\n", sec->segname, sec->sectname);
                hexdump(file + addr_32(sec->offset, type), addr_32(sec->size, type), addr_32(sec->addr, type), type);
            }

	        section += sizeof(struct section);
            section_numbers--;
	    }
    }
    return (TRUE);
}

// int get_sections_32(void *file, void *lc, int type, size_t file_size, t_list **lst)
// {
//     uint32_t        section_numbers;
// 	void            *section;
//     struct segment_command *seg;

//     seg = ((struct segment_command *)(lc));
//     if (get_errors_32(file, seg, type) == FALSE)
//         return (FALSE);
//     if (addr_32(seg->cmd, type) == LC_SEGMENT)
//     {
//         if (get_overflow_32(file, file + addr_32(seg->fileoff, type) + addr_32(seg->filesize, type), file_size) == FALSE)
//             return (FALSE);
//         section = lc + sizeof(struct segment_command);
//     	section_numbers = addr_32(((struct segment_command *)(lc))->nsects, type);
//         // Loop on sections
//         while (section_numbers)
//         {
//             struct section *sec = ((struct section *)(section));
// 	        // ft_printf("SECTION %s\n", sec->sectname);
//             if (ft_strcmp(sec->sectname, SECT_TEXT) == 0)
//             {
//                 if (get_overflow_32(file, file + addr_32(sec->offset, type) + addr_32(sec->size, type), file_size) == FALSE)
//                 return (FALSE);
//                 ft_printf("Contents of (%s,%s) section\n", sec->segname, sec->sectname);
//                 hexdump(file + addr_32(sec->offset, type), addr_32(sec->size, type), addr_32(sec->addr, type), type);
//             }

// 	        section += sizeof(struct section);
//             section_numbers--;
// 	    }
//     }
//     return (TRUE);
// }


int segment_command_handler_64(void *file, void *lc, size_t file_size)
{
    uint32_t        section_numbers;
	void            *section;

    if (get_errors_64(file, lc) == FALSE)
        return (FALSE);
    struct segment_command_64 *seg = ((struct segment_command_64 *)(lc));
    if (seg->cmd == LC_SEGMENT_64)
    {
        if (get_overflow_64(file, file + seg->fileoff + seg->filesize, file_size) == FALSE)
            return (FALSE);
        // ft_printf("SEGMENT %s\n", ((struct segment_command_64 *)(lc))->segname);
        section = lc + sizeof(struct segment_command_64);
    	section_numbers = ((struct segment_command_64 *)(lc))->nsects;
        // Loop on sections
        while (section_numbers)
        {
            struct section_64 *sec = ((struct section_64 *)(section));
	        // ft_printf("SECTION %s\n", sec->sectname);
            if (ft_strcmp(sec->sectname, SECT_TEXT) == 0)
            {
                if (get_overflow_64(file, file + sec->offset + sec->size, file_size) == FALSE)
                    return (FALSE);
                ft_printf("Contents of (%s,%s) section\n", sec->segname, sec->sectname);
                hexdump(file + sec->offset, sec->size, sec->addr, BIT64);
            }
	        section += sizeof(struct section_64);
            section_numbers--;
	    }
    }
    return (TRUE);
}

int segment_command_handler_32(void *file, void *lc, int type, size_t file_size)
{
    uint32_t        section_numbers;
	void            *section;
    struct segment_command *seg;

    seg = ((struct segment_command *)(lc));
    if (get_errors_32(file, seg, type) == FALSE)
        return (FALSE);
    if (addr_32(seg->cmd, type) == LC_SEGMENT)
    {
        if (get_overflow_32(file, file + addr_32(seg->fileoff, type) + addr_32(seg->filesize, type), file_size) == FALSE)
            return (FALSE);
        section = lc + sizeof(struct segment_command);
    	section_numbers = addr_32(((struct segment_command *)(lc))->nsects, type);
        // Loop on sections
        while (section_numbers)
        {
            struct section *sec = ((struct section *)(section));
	        // ft_printf("SECTION %s\n", sec->sectname);
            if (ft_strcmp(sec->sectname, SECT_TEXT) == 0)
            {
                if (get_overflow_32(file, file + addr_32(sec->offset, type) + addr_32(sec->size, type), file_size) == FALSE)
                return (FALSE);
                ft_printf("Contents of (%s,%s) section\n", sec->segname, sec->sectname);
                hexdump(file + addr_32(sec->offset, type), addr_32(sec->size, type), addr_32(sec->addr, type), type);
            }

	        section += sizeof(struct section);
            section_numbers--;
	    }
    }
    return (TRUE);
}
