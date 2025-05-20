/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 16:36:23 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/01/25 15:48:40 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/printf.h"

t_list	*ft_lstlast(t_list	*lst)
{
	if (lst)
		while (lst->next)
			lst = lst->next;
	return (lst);
}
