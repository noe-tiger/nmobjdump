/*
** EPITECH PROJECT, 2018
** *
** File description:
** *
*/

#include <stdio.h>
#include "Elf.h"

void	create_flags(int *val, char **types)
{
	types[ET_NONE] = "";
	val[ET_NONE] = 0x0;
	types[ET_REL] = "HAS_RELOC, HAS_SYMS";
	val[ET_REL] = 0x11;
	types[ET_EXEC] = "EXEC_P, HAS_SYMS, D_PAGED";
	val[ET_EXEC] = 0x112;
	types[ET_DYN] = "HAS_SYMS, DYNAMIC, D_PAGED";
	val[ET_DYN] = 0x150;
	types[ET_CORE] = "";
	val[ET_CORE] = 0x0;
}

void	print_header(elf_t *elf, char *file)
{
	int   val[ET_NUM];
	char  *types[ET_NUM];

	printf("\n");
	if (elf->ehdr->e_ident[EI_CLASS] == ELFCLASS64)
		printf("%s:\t file format elf64-x86-64\n", file);
	else
		printf("%s:\t file format elf32-i386\n", file);
	create_flags(val, types);
	if (elf->ehdr->e_type < ET_NUM)
	{
		printf("architecture: i386:x86-64, flags 0x%08x:\n",
		val[elf->ehdr->e_type]);
		printf("%s\n", types[elf->ehdr->e_type]);
		printf("start address 0x%016lx\n", elf->ehdr->e_entry);
	}
	printf("\n");
}
