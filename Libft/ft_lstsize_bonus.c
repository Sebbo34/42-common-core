/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:48:36 by sbo               #+#    #+#             */
/*   Updated: 2023/11/13 19:48:37 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)

{
	int		lenght;
	t_list	*element;

	lenght = 0;
	element = lst;
	while (element != NULL)
	{
		lenght++;
		element = element -> next;
	}
	return (lenght);
}
