/*
** EPITECH PROJECT, 2018
** *
** File description:
** *
*/

#include <stdlib.h>
#include <string.h>
#include "nm.h"

char	*clear(char *str)
{
	for (int i = 0; str[i]; i++)
		if (str[i] >= 'a' && str[i] <= 'z')
			str[i] -= 32;
	for (int i = 0; str[i]; i++)
	{
		if (str[i] < 'A' || str[i] > 'Z')
		{
			while (str[i])
			{
				str[i] = str[i + 1];
				i += 1;
			}
			i = -1;
		}
	}
	return (str);
}

list_t	*append(list_t *list, unsigned int ptr, char flag, char *func)
{
	list_t	*new = malloc(sizeof(list_t));
	list_t	*iter = list;

	if (!new)
		return (NULL);
	if (iter)
	{
		while (iter->next)
			iter = iter->next;
		iter->next = new;
	}
	else
		list = new;
	new->next = NULL;
	new->ptr = ptr;
	new->func = func;
	new->flag = flag;
	new->epur = clear(strdup(func));
	return (list);
}

int		swap(list_t *one, list_t *two)
{
	unsigned int	ptr;
	char		*func;

	if (strcmp(one->epur, two->epur) > 0)
	{
		ptr = one->ptr;
		one->ptr = two->ptr;
		two->ptr = ptr;
		ptr = one->flag;
		one->flag = two->flag;
		two->flag = ptr;
		func = one->func;
		one->func = two->func;
		two->func = func;
		func = one->epur;
		one->epur = two->epur;
		two->epur = func;
		return (1);
	}
	return (0);
}

void		sort(list_t *list)
{
	list_t	*tmp = list;

	if (!list)
		return ;
	while (tmp->next)
	{
		if (swap(tmp, tmp->next))
			tmp = list;
		else
			tmp = tmp->next;
	}
}
