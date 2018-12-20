/*
** EPITECH PROJECT, 2018
** *
** File description:
** *
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "obj.h"

void	print_end(int i, char *buf)
{
	if (i % 16 != 1)
		buf[(i % 16) - 1] = 0;
	while (i % 16 != 1)
	{
		if ((i % 4) == 0 && i != 0)
			printf(" ");
		printf("  ");
		i += 1;
	}
	printf(" %s\n", buf);
}

void	put_s(unsigned char *str, int size, size_t addr)
{
	char	buf[17];
	int	i = 0;

	printf(" %04lx ", addr);
	for (i = 1; i <= size; i++)
	{
		printf("%02x", str[i]);
		buf[(i - 1) % 16] = (isprint(str[i - 1]) ? str[i - 1] : '.');
		if ((i % 4) == 0 && i != 0)
			printf(" ");
		if ((i % 16) == 0 && i != 0 && i != size)
		{
			addr += 16;
			printf(" %s\n", buf);
			printf(" %04lx ", addr);
		}
	}
	print_end(i, buf);
}

void	print_obj(elf_t *elf, char *file, char *strtab, int i)
{
	if (strcmp(&strtab[elf->shdr[i].sh_name], ".bss") &&
	strcmp(&strtab[elf->shdr[i].sh_name], ".symtab") &&
	strcmp(&strtab[elf->shdr[i].sh_name], ".strtab") &&
	strcmp(&strtab[elf->shdr[i].sh_name], ".shstrtab") &&
	strcmp(&strtab[elf->shdr[i].sh_name], ".rela.text") &&
	strcmp(&strtab[elf->shdr[i].sh_name], ".note.GNU-stack") &&
	strcmp(&strtab[elf->shdr[i].sh_name], ".rela.eh_frame"))
	{
		if ((strcmp(&strtab[elf->shdr[i].sh_name], ".data") ||
		!(file[strlen(file) - 1] == 'o' &&
		file[strlen(file) - 2] == '.')))
		{
			printf("Contents of section %s:\n",
			&strtab[elf->shdr[i].sh_name]);
			put_s((unsigned char *)(elf->adr +
						elf->shdr[i].sh_offset),
			elf->shdr[i].sh_size, elf->shdr[i].sh_addr);
		}
	}
}

int	objdump(elf_t *elf, char *file)
{
	char *strtab = (char *)(elf->adr +
				elf->shdr[elf->ehdr->e_shstrndx].sh_offset);

	print_header(elf, file);
	for (int i = 1; i < elf->ehdr->e_shnum; i++)
		print_obj(elf, file, strtab, i);
	return (0);
}
