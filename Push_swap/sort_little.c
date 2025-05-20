/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_little.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 17:30:52 by sbo               #+#    #+#             */
/*   Updated: 2023/12/13 14:30:07 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_little(t_pile **pile_a, t_pile **pile_b)

{
	int	size;

	size = ft_lstsize(*pile_a);
	if (size == 2)
	{
		sa(pile_a);
		return ;
	}
	while (size > 3)
	{
		if (nbr_de_inf((*pile_a), (*pile_a)->nbr) == size - 4
			|| nbr_de_inf((*pile_a), (*pile_a)->nbr) == size - 5)
		{
			pb(pile_a, pile_b);
			size--;
		}
		else
			ra(pile_a);
	}
	if (test_tri(*pile_a) == 0)
		sort_pile_3(pile_a);
	while (*pile_b)
		pa(pile_b, pile_a);
	if ((*pile_a)->nbr > (*pile_a)->next->nbr)
		sa(pile_a);
}

void	sort_pile_3(t_pile **pile_a)

{
	t_pile	*suivant;
	t_pile	*dernier;

	suivant = (*pile_a)->next;
	dernier = suivant->next;
	if ((*pile_a)->nbr > suivant->nbr && (*pile_a)->nbr > dernier->nbr)
	{
		if (dernier->nbr > suivant->nbr)
			ra(pile_a);
		else
		{
			sa(pile_a);
			rra(pile_a);
		}
	}
	else if ((*pile_a)->nbr > suivant->nbr && (*pile_a)->nbr < dernier->nbr)
		sa(pile_a);
	else if (suivant->nbr > (*pile_a)->nbr && (*pile_a)->nbr > dernier->nbr)
		rra(pile_a);
	else if (suivant->nbr > (*pile_a)->nbr && (*pile_a)->nbr < dernier->nbr)
	{
		rra(pile_a);
		sa(pile_a);
	}
}
