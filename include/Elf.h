/*
** EPITECH PROJECT, 2018
** *
** File description:
** *
*/

#ifndef ELF_H_
# define ELF_H_

# include <elf.h>

typedef struct		elf_s
{
	void		*adr;
	Elf64_Ehdr	*ehdr;
	Elf64_Shdr	*shdr;
}			elf_t;

int		init_elf(char *, elf_t *);

#endif /* !ELF_H_ */
