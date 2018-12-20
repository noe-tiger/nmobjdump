/*
** EPITECH PROJECT, 2018
** *
** File description:
** *
*/

#include <stdlib.h>
#include "obj.h"

int	main(int ac, char **av)
{
	elf_t	elf;

	if (ac == 1)
	{
		av[1] = "a.out";
		av[2] = NULL;
	}
	init_elf(av[1], &elf);
	return (objdump(&elf, av[1]));
}
