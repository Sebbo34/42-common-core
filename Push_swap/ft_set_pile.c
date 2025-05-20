/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_pile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 17:50:25 by sbo               #+#    #+#             */
/*   Updated: 2023/12/12 16:37:46 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	set_b(t_pile **b, int i)

{
	int	j;

	j = 0;
	if (i > 0)
	{
		while (j < i)
		{
			rb(b);
			j++;
		}
	}
	else
	{
		while (i < j)
		{
			rrb(b);
			i++;
		}
	}
}

void	set_a(t_pile **a, int i)

{
	int	j;

	j = 0;
	if (i > 0)
	{
		while (j < i)
		{
			ra(a);
			j++;
		}
	}
	else
	{
		while (i < j)
		{
			rra(a);
			i++;
		}
	}
}

void	set_ab(t_pile **a, t_pile **b, int i, int j)
{	
	if (i > 0 && j > 0)
	{
		while (i > 0 && j > 0)
		{
			i--;
			j--;
			rr(a, b);
		}
	}
	else if (i < 0 && j < 0)
	{
		while (0 > i && 0 > j)
		{
			i++;
			j++;
			rrr(a, b);
		}
	}
	set_a(a, j);
	set_b(b, i);
}
