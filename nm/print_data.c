/*
** EPITECH PROJECT, 2018
** *
** File description:
** *
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "nm.h"

char		get_type(int type, int flags, int info, int value)
{
	char	res;

	res = 'U';
	if (type == SHT_NOBITS && flags == (SHF_WRITE + SHF_ALLOC))
		res = 'B';
	if ( (type == SHT_PROGBITS || type == SHT_DYNAMIC)
	&& flags == (SHF_WRITE + SHF_ALLOC))
		res = 'D';
	if (type == SHT_PROGBITS && flags == SHF_ALLOC)
		res = 'R';
	if (type > SHT_DYNSYM)
		res = 'T';
	if (type == SHT_PROGBITS && flags == (SHF_ALLOC + SHF_EXECINSTR))
		res = 'T';
	if (ELF64_ST_BIND(info) == STB_WEAK)
		res = 'W';
	if ((ELF64_ST_BIND(info) == STB_LOCAL || value == 0) && res != 'U')
		res += 32;
	return (res);
}

void	print(list_t *list)
{
	if (!list)
		return ;
	while (list)
	{
		if (list->ptr || list->flag == 'T' || list->flag == 't')
			printf("%016x %c %s\n", list->ptr,
			list->flag, list->func);
		else
			printf("                 %c %s\n",
			list->flag, list->func);
		list = list->next;
	}
}

list_t	*create_list(elf_t *elf, int i, Elf64_Sym *sym, char *str)
{
	list_t		*list = NULL;
	int		size;

	size = elf->shdr[i].sh_size / sizeof(Elf64_Sym);
	for (int j = 1; j < size; j++)
	{
		while ((sym[j].st_shndx > 60000 ||
			!strlen(strdup(&str[sym[j].st_name])))
		&& size > j)
			j++;
		list = append(list, (unsigned int)sym[j].st_value,
			get_type(elf->shdr[sym[j].st_shndx].sh_type,
				elf->shdr[sym[j].st_shndx].sh_flags,
				sym[j].st_info,
				sym[j].st_value),
			strdup(&str[sym[j].st_name]));
		if (!list)
			return (NULL);
	}
	return (list);
}

int	print_data(elf_t *elf)
{
	list_t		*list;
	Elf64_Sym	*sym;
	char		*str;

	list = NULL;
	for (int i = 0; i < elf->ehdr->e_shnum; i++)
	{
		if (elf->shdr[i].sh_type == SHT_SYMTAB)
		{
			sym = elf->adr + elf->shdr[i].sh_offset;
			str = elf->adr +
				elf->shdr[elf->shdr[i].sh_link].sh_offset;
			list = create_list(elf, i, sym, str);
			if (!list)
				return (-1);
		}
	}
	sort(list);
	print(list);
	return (0);
}
