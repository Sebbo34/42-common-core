/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 17:41:46 by seb               #+#    #+#             */
/*   Updated: 2024/01/22 17:46:49 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_maps	*ft_lstnew(void *content, int *y)
{
	t_maps	*element;

	element = malloc (sizeof(t_maps));
	element -> line = content;
	element -> next = NULL;
	element -> y = *y;
	*y = *y + 1;
	return (element);
}

t_maps	*ft_lstlast(t_maps *lst)
{
	if (!lst)
		return (NULL);
	while (lst -> next)
	{
		lst = lst -> next;
	}
	return (lst);
}

void	ft_lstadd_back(t_maps **lst, t_maps *new)
{
	t_maps	*last;

	if (!(*lst))
		*lst = new;
	else
	{
		last = ft_lstlast(*lst);
		last -> next = new;
	}
	new -> next = NULL;
}

void	ft_lstclear(t_maps **lst)
{
	t_maps	*ptr;

	if (!lst)
	{
		return ;
	}
	while (*lst)
	{
		ptr = (*lst)->next;
		free((*lst)->line);
		free(*lst);
		*lst = ptr;
	}
	lst = NULL;
}
