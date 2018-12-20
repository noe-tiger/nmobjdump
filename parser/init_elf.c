/*
** EPITECH PROJECT, 2018
** *
** File description:
** *
*/

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include "Elf.h"

void	fit_ehdr(Elf64_Ehdr *ehdr, Elf32_Ehdr *buf)
{
	memcpy(ehdr->e_ident, buf->e_ident, EI_NIDENT);
	ehdr->e_type = buf->e_type;
	ehdr->e_machine = buf->e_machine;
	ehdr->e_version = buf->e_version;
	ehdr->e_entry = buf->e_entry;
	ehdr->e_phoff = buf->e_phoff;
	ehdr->e_shoff = buf->e_shoff;
	ehdr->e_flags = buf->e_flags;
	ehdr->e_ehsize = buf->e_ehsize;
	ehdr->e_phentsize = buf->e_phentsize;
	ehdr->e_phnum = buf->e_phnum;
	ehdr->e_shentsize = buf->e_shentsize;
	ehdr->e_shnum = buf->e_shnum;
	ehdr->e_shstrndx = buf->e_shstrndx;
}

void	fit_shdr(Elf64_Shdr *shdr, Elf32_Shdr *buf, size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		shdr[i].sh_name = buf[i].sh_name;
		shdr[i].sh_type = buf[i].sh_type;
		shdr[i].sh_flags = buf[i].sh_flags;
		shdr[i].sh_addr = buf[i].sh_addr;
		shdr[i].sh_offset = buf[i].sh_offset;
		shdr[i].sh_size = buf[i].sh_size;
		shdr[i].sh_link = buf[i].sh_link;
		shdr[i].sh_info = buf[i].sh_info;
		shdr[i].sh_addralign = buf[i].sh_addralign;
		shdr[i].sh_entsize = buf[i].sh_entsize;
	}
}

int	get_info(void *buf, elf_t *elf)
{
	elf->adr = buf;
	elf->ehdr = elf->adr;
	elf->shdr = elf->adr + elf->ehdr->e_shoff;
	if (elf->ehdr->e_ident[EI_CLASS] == ELFCLASS32)
	{
		elf->ehdr = malloc(sizeof(Elf64_Ehdr));
		if (!elf->ehdr)
			return (-1);
		fit_ehdr(elf->ehdr, buf);
		elf->shdr = malloc(sizeof(Elf64_Shdr) * elf->ehdr->e_shnum);
		if (!elf->shdr)
			return (-1);
		fit_shdr(elf->shdr, (void *)(elf->adr + elf->ehdr->e_shoff),
			elf->ehdr->e_shnum);
	}
	if (elf->ehdr->e_shstrndx == SHN_UNDEF)
		return (-1);
	return (0);
}

int	init_elf(char *file, elf_t *elf)
{
	int		fd;
	void		*buf;
	struct		stat s;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (-1);
	fstat(fd, &s);
	buf = mmap(NULL , s.st_size , PROT_READ , MAP_PRIVATE , fd, 0);
	close(fd);
	if (buf == (void *)-1)
		return (-1);
	if (get_info(buf, elf) == -1)
		return (-1);
	return (s.st_size);
}
