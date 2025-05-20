/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_command_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 17:21:35 by sbo               #+#    #+#             */
/*   Updated: 2023/12/13 17:21:36 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push(t_pile **a, t_pile **b)
{
	t_pile	*temp;

	if (!(*a))
		return ;
	temp = (*a)->next;
	if (temp != NULL)
	{
		(*a)->next = (*b);
		(*b) = (*a);
		(*a) = temp;
	}
	else
	{
		(*a)->next = *b;
		(*b) = (*a);
		(*a) = NULL;
	}
}

void	rev_rota(t_pile **a)

{
	t_pile	*temp;
	t_pile	*premier;

	temp = NULL;
	if (!(*a))
		return ;
	if ((*a)->next == NULL)
		return ;
	premier = *a;
	while ((*a)->next)
	{
		temp = (*a);
		(*a) = (*a)->next;
	}
	temp -> next = NULL;
	(*a)->next = premier;
}

void	rota(t_pile **a)

{
	t_pile	*temp;
	t_pile	*premier;

	if (!(*a))
		return ;
	if ((*a)->next == NULL)
		return ;
	temp = *a;
	premier = (*a)->next;
	while ((*a)->next)
		(*a) = (*a)->next;
	(*a)->next = temp;
	temp -> next = NULL;
	(*a) = premier;
}

void	swap(t_pile **a)

{
	t_pile	*temp;

	temp = (*a)->next ;
	if (temp != NULL)
	{
	(*a)->next = temp -> next;
	temp -> next = (*a);
	(*a) = temp;
	}
}

void	d_rev_rota(t_pile **a, t_pile **b)

{
	rev_rota(a);
	rev_rota(b);
}
