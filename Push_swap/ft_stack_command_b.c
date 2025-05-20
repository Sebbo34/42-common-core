/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_command_b.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 18:03:08 by sbo               #+#    #+#             */
/*   Updated: 2023/12/12 16:39:31 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	pb(t_pile **a, t_pile **b)
{
	t_pile	*temp;

	temp = (*a)->next;
	if (!(*a))
		return ;
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
	write(1, "pb\n", 3);
}

void	rrb(t_pile **a)

{
	t_pile	*temp;
	t_pile	*premier;

	premier = *a;
	while ((*a)->next)
	{
		temp = (*a);
		(*a) = (*a)->next;
	}
	temp -> next = NULL;
	(*a)->next = premier;
	write(1, "rrb\n", 4);
}

void	rb(t_pile **a)

{
	t_pile	*temp;
	t_pile	*premier;

	if ((*a)->next == NULL)
		return ;
	temp = *a;
	premier = (*a)->next;
	while ((*a)->next)
		(*a) = (*a)->next;
	(*a)->next = temp;
	temp -> next = NULL;
	(*a) = premier;
	write(1, "rb\n", 3);
}

void	sb(t_pile **a)

{
	t_pile	*temp;

	temp = (*a)->next ;
	if (temp != NULL)
	{
	(*a)->next = temp -> next;
	temp -> next = (*a);
	(*a) = temp;
	}
	write(1, "sb\n", 3);
}

void	rrr(t_pile **a, t_pile **b)

{
	t_pile	*temp;
	t_pile	*premier;

	premier = *a;
	while ((*a)->next)
	{
		temp = (*a);
		(*a) = (*a)->next;
	}
	temp->next = NULL;
	(*a)->next = premier;
	premier = *b;
	while ((*b)->next)
	{
		temp = (*b);
		(*b) = (*b)->next;
	}
	temp->next = NULL;
	(*b)->next = premier;
	write(1, "rrr\n", 4);
}
