/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 18:41:33 by sbo               #+#    #+#             */
/*   Updated: 2023/11/11 18:41:48 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char	*src)

{
	char	*cpy;
	int		cpt;

	cpy = (char *)malloc(ft_strlen(src) + 1);
	if (cpy == NULL)
		return (NULL);
	cpt = 0;
	while (src[cpt] != '\0')
	{
		cpy[cpt] = src [cpt];
		cpt++;
	}
	cpy[cpt] = '\0';
	return (cpy);
}
