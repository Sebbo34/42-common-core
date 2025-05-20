/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 23:18:06 by seb               #+#    #+#             */
/*   Updated: 2023/11/15 23:21:15 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))

{
	if (!lst)
		return ;
	while (lst -> next)
	{
		(*f)(lst -> content);
		lst = lst -> next;
	}
	(*f)(lst -> content);
}
