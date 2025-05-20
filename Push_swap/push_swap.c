/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 11:52:20 by sbo               #+#    #+#             */
/*   Updated: 2023/12/15 10:54:33 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sommet_min(t_pile **pile_a)

{
	int		i;
	int		index;
	t_pile	*temp;

	index = 0;
	temp = *pile_a;
	i = 0;
	while (temp)
	{
		if (stack_min(*pile_a) == temp->nbr)
			index = i;
		i++;
		temp = temp -> next;
	}
	if (index > i / 2)
	{
		while (index++ < i)
			rra(pile_a);
	}
	else
	{
		while (index-- > 0)
			ra(pile_a);
	}
}

void	push_swap(t_pile **pile_a, t_pile **pile_b)

{
	int	i;
	int	j;

	i = 0;
	push_sort(pile_a, pile_b);
	while (*pile_b)
	{
		if ((*pile_b)->next)
		{
			i = pick((*pile_a), (*pile_b));
			j = place ((*pile_a), recup_b((*pile_b), i));
			set_ab(pile_a, pile_b, i, j);
		}
		else
		{
			j = place ((*pile_a), (*pile_b)->nbr);
			set_a(pile_a, j);
		}
		pa(pile_b, pile_a);
	}
	sommet_min(pile_a);
}

int	main(int argc, char *argv[])

{
	t_pile	*pile_a;
	t_pile	*pile_b;

	if (error_manage(argv, argc) == 0 || argc < 2)
		return (0);
	pile_a = NULL;
	pile_b = NULL;
	pile_a = ft_create_stack(argv, argc);
	if (!pile_a)
		return (0);
	if (ft_isonly(pile_a) == 0 || test_tri(pile_a) == 1)
	{
		ft_lstclear(&pile_a);
		return (0);
	}
	else if (argc <= 6)
		sort_little(&pile_a, &pile_b);
	else
		push_swap (&pile_a, &pile_b);
	ft_lstclear(&pile_a);
	return (0);
}
