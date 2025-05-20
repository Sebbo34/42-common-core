/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:16:03 by sbo               #+#    #+#             */
/*   Updated: 2023/11/16 15:16:04 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void*), void(*del)(void *))

{
	t_list	*suivant;
	t_list	*premier;
	void	*content;

	if (!lst)
		return (NULL);
	content = (*f)(lst -> content);
	suivant = ft_lstnew(content);
	if (suivant == NULL)
		return (NULL);
	premier = suivant;
	while (lst -> next)
	{
		lst = lst -> next;
		content = (*f)(lst -> content);
		suivant = ft_lstnew(content);
		if (suivant == NULL)
		{
			(*del)(content);
			ft_lstclear(&premier, del);
			return (NULL);
		}
		ft_lstadd_back(&premier, suivant);
	}
	return (premier);
}
