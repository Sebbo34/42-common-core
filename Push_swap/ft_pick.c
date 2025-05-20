/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pick.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 17:57:34 by sbo               #+#    #+#             */
/*   Updated: 2023/12/12 16:35:43 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	remplir_tab(t_pile *a, t_pile *b, int *tab)

{
	tab[0] = 0;
	tab[1] = 0;
	tab[2] = ft_lstsize(b);
	tab[3] = abs(place(a, b->nbr) + tab[0]);
}

void	asgn(int *tab, int inf, int index, int min)

{
	if (inf < tab[3])
	{
		tab[1] = index;
		tab[3] = min;
	}
}

int	pick(t_pile *a, t_pile *b)

{
	int	tab[5];

	remplir_tab(a, b, tab);
	while (b)
	{
		tab[4] = place(a, b -> nbr);
		if (tab[4] > 0 && tab[0] < tab[2] / 2)
			asgn(tab, ft_max(tab[0], tab[4]), tab[0], ft_max(tab[0], tab[4]));
		else if (tab[4] < 0 && tab[0] > tab[2] / 2)
			asgn(tab, ft_max (abs(tab[4]), tab[2] - tab[0]),
				-(tab[2] - tab[0]), ft_max(abs(tab[4]), tab[2] - tab[0]));
		else
		{
			if (tab[0] > tab[2] / 2)
				asgn(tab, tab[4] + tab[2] - tab[0],
					-(tab[2] - tab[0]), tab[4] + tab[2] - tab[0]);
			else
				asgn(tab, abs(tab[4]) + tab[0], tab[0], abs(tab[4]) + tab[0]);
		}
		b = b -> next;
		tab[0]++;
	}
	return (tab[1]);
}

int	recup_b(t_pile *b, int i)

{
	int	j;

	j = 0;
	if (i >= 0)
	{
		while (j < i && b)
		{
			b = b->next;
			j++;
		}
	}
	else
	{
		b = reverse(b, -i);
	}
	return (b->nbr);
}
