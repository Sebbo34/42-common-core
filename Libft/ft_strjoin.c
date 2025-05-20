/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:29:27 by sbo               #+#    #+#             */
/*   Updated: 2023/11/13 15:00:16 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)

{
	int		length;
	size_t	cpt;
	size_t	cpt2;
	char	*chaine;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	length = ft_strlen(s1) + ft_strlen(s2);
	chaine = malloc(length + 1);
	if (chaine == NULL)
		return (NULL);
	cpt = -1;
	cpt2 = 0;
	while (++cpt < ft_strlen(s1))
		chaine[cpt] = s1[cpt];
	while (cpt2 < ft_strlen(s2))
	{
		chaine[cpt] = s2[cpt2];
		cpt2++;
		cpt++;
	}
	chaine[cpt] = '\0';
	return (chaine);
}
