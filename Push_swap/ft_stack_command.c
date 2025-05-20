/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 13:43:30 by sbo               #+#    #+#             */
/*   Updated: 2023/12/12 16:40:27 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	pa(t_pile **a, t_pile **b)
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
	write(1, "pa\n", 3);
}

void	rra(t_pile **a)

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
	write(1, "rra\n", 4);
}

void	ra(t_pile **a)

{
	t_pile	*temp;
	t_pile	*premier;

	if ((*a)->next == NULL)
		return ;
	temp = *a;
	premier = (*a)->next;
	while ((*a)->next)
	{
		(*a) = (*a)->next;
	}
	(*a)->next = temp;
	temp->next = NULL;
	(*a) = premier;
	write(1, "ra\n", 3);
}

void	sa(t_pile **a)

{
	t_pile	*temp;

	temp = (*a)->next;
	if (temp != NULL)
	{
		(*a)->next = temp->next;
		temp->next = (*a);
		(*a) = temp;
	}
	write(1, "sa\n", 3);
}

void	rr(t_pile **a, t_pile **b)

{
	t_pile	*temp;
	t_pile	*premier;

	temp = *a;
	premier = (*a)->next;
	while ((*a)->next)
		(*a) = (*a)->next;
	(*a)->next = temp;
	temp->next = NULL;
	(*a) = premier;
	temp = *b;
	premier = (*b)->next;
	while ((*b)->next)
		(*b) = (*b)->next;
	(*b)->next = temp;
	temp->next = NULL;
	(*b) = premier;
	write(1, "rr\n", 3);
}
