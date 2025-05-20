/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 17:55:11 by sbo               #+#    #+#             */
/*   Updated: 2023/12/12 16:36:53 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	nbr_de_inf(t_pile *a, int n)

{
	int	i;

	i = 0;
	while (a)
	{
		if (a->nbr < n)
			i++;
		a = a->next;
	}
	return (i);
}

int	ft_quartile(t_pile *a, int valeur)
{
	t_pile	*temp;

	temp = a;
	while (a)
	{
		if (nbr_de_inf(temp, a->nbr) == valeur)
		{
			return (a->nbr);
		}
		a = a->next;
	}	
	return (0);
}

void	attribute(int *tab, t_pile *a)

{
	tab[0] = 0;
	tab[1] = ft_lstsize(a);
	tab[2] = ft_quartile (a, tab[1] / 4);
	tab[3] = ft_quartile(a, tab[1] / 2);
	tab[4] = ft_quartile (a, (tab[1] * 3) / 4);
}

void	push_sort(t_pile **a, t_pile **b)

{
	int	tab[5];

	attribute(tab,*a);
	while (tab[0]++ < tab[1])
	{
		if ((*a)->nbr < tab[2])
			pb(a, b);
		else if ((*a)->nbr >= tab[4])
		{
			pb(a, b);
			rb(b);
		}
		else
			ra(a);
	}
	while ((*a)->next)
	{
		if ((*a)->nbr <= tab[3])
			pb(a, b);
		else
		{
			pb(a, b);
			rb(b);
		}
	}
}
