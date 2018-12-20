/*
** EPITECH PROJECT, 2018
** *
** File description:
** *
*/

#include <stdlib.h>
#include "nm.h"

int		main(int ac , char **av)
{
	elf_t	elf;
	int	size;

	if (ac < 2)
	{
		av[1] = "a.out";
		av[2] = NULL;
	}
	size = init_elf(av[1], &elf);
	if (size == -1)
		return (84);
	return (print_data(&elf));
}
