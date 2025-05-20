/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_stack.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 17:12:32 by sbo               #+#    #+#             */
/*   Updated: 2023/12/13 18:52:07 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_pile	*ft_create_stack(char **tab, int lenght)

{
	t_pile	*premier;
	t_pile	*element;
	int		i;

	i = 2;
	element = ft_lstnew(ft_atoi(tab[1]));
	if (!element)
		return (NULL);
	premier = element;
	while (i < lenght)
	{
		element = ft_lstnew(ft_atoi(tab[i]));
		if (!element)
			return (NULL);
		ft_lstadd_back(&premier, element);
		i++;
	}
	return (premier);
}
