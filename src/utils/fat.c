/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 17:37:34 by ndubouil          #+#    #+#             */
/*   Updated: 2020/10/21 14:54:20 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm-otool.h"

static t_arch_flag arch_flags[] = {
    { "any",	CPU_TYPE_ANY,	  CPU_SUBTYPE_MULTIPLE },
    { "little",	CPU_TYPE_ANY,	  CPU_SUBTYPE_LITTLE_ENDIAN },
    { "big",	CPU_TYPE_ANY,	  CPU_SUBTYPE_BIG_ENDIAN },

/* 64-bit Mach-O architectures */

    /* architecture families */
    { "ppc64",     CPU_TYPE_POWERPC64, CPU_SUBTYPE_POWERPC_ALL },
    { "x86_64",    CPU_TYPE_X86_64, CPU_SUBTYPE_X86_64_ALL },
    { "x86_64h",   CPU_TYPE_X86_64, CPU_SUBTYPE_X86_64_H },
    { "arm64",     CPU_TYPE_ARM64,     CPU_SUBTYPE_ARM64_ALL },
    /* specific architecture implementations */
    { "ppc970-64", CPU_TYPE_POWERPC64, CPU_SUBTYPE_POWERPC_970 },

/* 32-bit Mach-O architectures */

    /* architecture families */
    { "ppc",    CPU_TYPE_POWERPC, CPU_SUBTYPE_POWERPC_ALL },
    { "i386",   CPU_TYPE_I386,    CPU_SUBTYPE_I386_ALL },
    { "m68k",   CPU_TYPE_MC680x0, CPU_SUBTYPE_MC680x0_ALL },
    { "hppa",   CPU_TYPE_HPPA,    CPU_SUBTYPE_HPPA_ALL },
    { "sparc",	CPU_TYPE_SPARC,   CPU_SUBTYPE_SPARC_ALL },
    { "m88k",   CPU_TYPE_MC88000, CPU_SUBTYPE_MC88000_ALL },
    { "i860",   CPU_TYPE_I860,    CPU_SUBTYPE_I860_ALL },
    { "veo",    CPU_TYPE_VEO,     CPU_SUBTYPE_VEO_ALL },
    { "arm",    CPU_TYPE_ARM,     CPU_SUBTYPE_ARM_ALL },
    /* specific architecture implementations */
    { "ppc601", CPU_TYPE_POWERPC, CPU_SUBTYPE_POWERPC_601 },
    { "ppc603", CPU_TYPE_POWERPC, CPU_SUBTYPE_POWERPC_603 },
    { "ppc603e",CPU_TYPE_POWERPC, CPU_SUBTYPE_POWERPC_603e },
    { "ppc603ev",CPU_TYPE_POWERPC,CPU_SUBTYPE_POWERPC_603ev },
    { "ppc604", CPU_TYPE_POWERPC, CPU_SUBTYPE_POWERPC_604 },
    { "ppc604e",CPU_TYPE_POWERPC, CPU_SUBTYPE_POWERPC_604e },
    { "ppc750", CPU_TYPE_POWERPC, CPU_SUBTYPE_POWERPC_750 },
    { "ppc7400",CPU_TYPE_POWERPC, CPU_SUBTYPE_POWERPC_7400 },
    { "ppc7450",CPU_TYPE_POWERPC, CPU_SUBTYPE_POWERPC_7450 },
    { "ppc970", CPU_TYPE_POWERPC, CPU_SUBTYPE_POWERPC_970 },
    { "i486",   CPU_TYPE_I386,    CPU_SUBTYPE_486 },
    { "i486SX", CPU_TYPE_I386,    CPU_SUBTYPE_486SX },
    { "pentium",CPU_TYPE_I386,    CPU_SUBTYPE_PENT }, /* same as i586 */
    { "i586",   CPU_TYPE_I386,    CPU_SUBTYPE_586 },
    { "pentpro", CPU_TYPE_I386, CPU_SUBTYPE_PENTPRO }, /* same as i686 */
    { "i686",   CPU_TYPE_I386, CPU_SUBTYPE_PENTPRO },
    { "pentIIm3",CPU_TYPE_I386, CPU_SUBTYPE_PENTII_M3 },
    { "pentIIm5",CPU_TYPE_I386, CPU_SUBTYPE_PENTII_M5 },
    { "pentium4",CPU_TYPE_I386, CPU_SUBTYPE_PENTIUM_4 },
    { "m68030", CPU_TYPE_MC680x0, CPU_SUBTYPE_MC68030_ONLY },
    { "m68040", CPU_TYPE_MC680x0, CPU_SUBTYPE_MC68040 },
    { "hppa7100LC", CPU_TYPE_HPPA,  CPU_SUBTYPE_HPPA_7100LC },
    { "veo1",   CPU_TYPE_VEO,     CPU_SUBTYPE_VEO_1 },
    { "veo2",   CPU_TYPE_VEO,     CPU_SUBTYPE_VEO_2 },
    { "veo3",   CPU_TYPE_VEO,     CPU_SUBTYPE_VEO_3 },
    { "veo4",   CPU_TYPE_VEO,     CPU_SUBTYPE_VEO_4 },
    { "armv4t", CPU_TYPE_ARM,     CPU_SUBTYPE_ARM_V4T},
    { "armv5",  CPU_TYPE_ARM,     CPU_SUBTYPE_ARM_V5TEJ},
    { "xscale", CPU_TYPE_ARM,     CPU_SUBTYPE_ARM_XSCALE},
    { "armv6",  CPU_TYPE_ARM,     CPU_SUBTYPE_ARM_V6 },
    { "armv6m", CPU_TYPE_ARM,     CPU_SUBTYPE_ARM_V6M },
    { "armv7",  CPU_TYPE_ARM,     CPU_SUBTYPE_ARM_V7 },
    { "armv7f", CPU_TYPE_ARM,     CPU_SUBTYPE_ARM_V7F },
    { "armv7s", CPU_TYPE_ARM,     CPU_SUBTYPE_ARM_V7S },
    { "armv7k", CPU_TYPE_ARM,     CPU_SUBTYPE_ARM_V7K },
    { "armv7m", CPU_TYPE_ARM,     CPU_SUBTYPE_ARM_V7M },
    { "armv7em", CPU_TYPE_ARM,    CPU_SUBTYPE_ARM_V7EM },
    { "arm64v8",CPU_TYPE_ARM64,   CPU_SUBTYPE_ARM64_V8 },
    { NULL,	0,		  0 }
};

static char		*get_architecture(cpu_type_t cputype, cpu_subtype_t cpusubtype)
{
	int i;

	i = 0;
	while (arch_flags[i].name)
	{
		if (cputype == arch_flags[i].cputype
			&& cpusubtype == arch_flags[i].cpusubtype)
			return (arch_flags[i].name);
		i++;
	}
	return (NULL);
}

static int manage_fat(void *file, size_t size, int t, void *arch)
{
    int         type;

    struct fat_arch *a = ((struct fat_arch *)(arch));
    if (get_overflow_32(file, file + addr_32(a->offset, t), size) == FALSE)
        return (FALSE);
    if ((type = is_macho(file + addr_32(a->offset, t), t & NM)) == FALSE)
        return (FALSE);
    object_handler(file + addr_32(a->offset, t), type, addr_32(a->size, t));
	return (TRUE);
}

static int is_our_cpu(int type, void *arch)
{
    struct fat_arch *a = ((struct fat_arch *)(arch));

    if (addr_32(a->cputype, type) == CPU_TYPE_X86_64)
    {
        return (TRUE);
    }
	return (FALSE);
}

int fat_handler(void *file, int type, size_t size)
{
	struct fat_arch		*arch;
	uint32_t	        numbers_arch;
    uint32_t                 i;
    int                 x86;
	// arch = ((struct fat_header *)(file))->nfat_arch;
	arch = file + sizeof(struct fat_header);
    x86 = FALSE;
    if (type & L_ENDIAN)
    {
        numbers_arch = uint32_swap(((struct fat_header *)(file))->nfat_arch);
    }
    else
    {
        numbers_arch = ((struct fat_header *)(file))->nfat_arch;
    }
    i = 0;
    while (i < numbers_arch)
	{
        if (get_overflow_32(file, file + addr_32(((struct fat_arch *)(arch))->offset, type), size) == FALSE)
            return (FALSE);
        if (is_our_cpu(type, arch))
        {
            x86 = TRUE;
        }
	    arch = (void *)arch + sizeof(struct fat_arch);   
        i++;
    }
	arch = file + sizeof(struct fat_header);
    i = 0;
    while (i < numbers_arch)
	{
        if (addr_32(((struct fat_arch *)(arch))->cputype, type) != CPU_TYPE_X86_64 && x86)
        {
	        arch = (void *)arch + sizeof(struct fat_arch);   
            i++;
            continue;
        }
        else if (!x86)
        {
            ft_printf("filename (architecture %s) :\n", get_architecture(addr_32(((struct fat_arch *)(arch))->cputype, type), addr_32(((struct fat_arch *)(arch))->cpusubtype, type)));
        }
        manage_fat(file, size, type, arch);
        if (x86)
        {
            break;
        }
	    arch = (void *)arch + sizeof(struct fat_arch);   
        i++;
    }
	return (TRUE);
}
