/*
** EPITECH PROJECT, 2018
** *
** File description:
** *
*/

#ifndef NM_H_
# define NM_H_

# include "Elf.h"

typedef struct	list_s
{
	unsigned int	ptr;
	char		*func;
	char		*epur;
	char		flag;

	struct	list_s	*next;
}		list_t;

list_t	*append(list_t *, unsigned int, char, char *);
void	sort(list_t *);
int	print_data(elf_t *);

#endif /* !NM_H_ */
