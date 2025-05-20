/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 17:30:01 by sbo               #+#    #+#             */
/*   Updated: 2023/12/13 17:30:02 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	stack_min(t_pile *pile_a)

{
	int	min;
	int	i;
	int	index;

	index = 0;
	i = 0;
	min = pile_a -> nbr;
	while (pile_a)
	{
		if (min > pile_a -> nbr)
			min = pile_a -> nbr;
		i++;
		pile_a = pile_a -> next;
	}
	return (min);
}

int	stack_max(t_pile *pile_a)

{
	int	max;
	int	i;
	int	index;

	index = 0;
	i = 0;
	max = pile_a -> nbr;
	while (pile_a)
	{
		if (max < pile_a -> nbr)
		{
			max = pile_a -> nbr;
		}
		i++;
		pile_a = pile_a -> next;
	}
	return (max);
}

int	ft_abs(int n)

{
	if (n > 0)
		return (n);
	else
		return (-n);
}

int	ft_max(int i, int j)
{
	if (i > j)
		return (i);
	else
		return (j);
}

int	test_tri(t_pile *stack)
{
	t_pile	*temp;

	if (!stack)
		return (0);
	temp = stack->next;
	while (temp)
	{
		if (stack->nbr > temp->nbr)
			return (0);
		stack = temp;
		temp = (stack)->next;
	}
	return (1);
}
