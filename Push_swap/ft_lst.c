/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 17:21:16 by sbo               #+#    #+#             */
/*   Updated: 2023/12/13 17:21:17 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_pile	*ft_lstnew(int nbr)
{
	t_pile	*element;

	element = malloc (sizeof(t_pile));
	if (element == NULL)
		return (NULL);
	element -> nbr = nbr;
	element -> next = NULL;
	return (element);
}

t_pile	*ft_lstlast(t_pile *lst)

{
	if (!lst)
		return (NULL);
	while (lst -> next)
	{
		lst = lst -> next;
	}
	return (lst);
}

void	ft_lstadd_back(t_pile **lst, t_pile *new)

{
	t_pile	*last;

	if (!(*lst))
		*lst = new;
	else
	{
		last = ft_lstlast(*lst);
		last -> next = new;
	}
	new -> next = NULL;
}

void	ft_lstclear(t_pile **lst)
{
	t_pile	*ptr;

	if (!lst)
	{
		return ;
	}
	while (*lst)
	{
		ptr = (*lst)->next;
		free(*lst);
		*lst = ptr;
	}
	lst = NULL;
}

int	ft_lstsize(t_pile *lst)

{
	int		lenght;
	t_pile	*element;

	lenght = 0;
	element = lst;
	while (element != NULL)
	{
		lenght++;
		element = element -> next;
	}
	return (lenght);
}
