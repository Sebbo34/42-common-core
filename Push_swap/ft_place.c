/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_place.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 17:56:35 by sbo               #+#    #+#             */
/*   Updated: 2023/12/12 16:36:12 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_pile	*reverse(t_pile *stack, int index)

{
	int	l;
	int	i;

	i = 0;
	l = ft_lstsize(stack);
	while (i < (l - index) && stack -> next)
	{
		i++;
		stack = stack->next;
	}
	return (stack);
}

int	set_index(t_pile *a, t_pile *premier, int *tab)

{
	if (a -> next)
	{
		if ((a->nbr == tab[1]) && tab[3] < a->nbr)
			return (tab[0]);
		if ((a->nbr == tab[2]) && tab[3] > a->nbr)
			return (tab[0] + 1);
		if (tab[3] > a->nbr && a->next->nbr > tab[3])
			return (tab[0] + 1);
	}
	else
	{
		if (((a->nbr == tab[1]) && tab[3] < a->nbr))
			return (tab[0]);
		if ((a->nbr == tab[2]) && tab[3] > a->nbr)
			return (tab[0] + 1);
		if (a->nbr < tab[3] && tab[3] < premier->nbr)
			return (tab[0] + 1);
	}
	return (-1);
}

int	place(t_pile *a, int n)

{
	int		index;
	int		j;
	t_pile	*premier;
	int		tab[4];

	premier = a;
	index = 0;
	tab[0] = 0;
	tab[1] = stack_min(a);
	tab[2] = stack_max(a);
	tab[3] = n;
	while (a)
	{
		j = set_index(a, premier, tab);
		if (j != -1)
			index = j;
		a = a->next;
		tab[0]++;
	}
	if (index > tab[0] / 2)
		return (index - tab[0]);
	else
		return (index);
}
