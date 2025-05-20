/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 20:02:11 by seb               #+#    #+#             */
/*   Updated: 2023/11/11 19:11:35 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))

{
	int		cpt;
	char	*chaine;

	if (s == NULL)
		return (NULL);
	chaine = malloc(ft_strlen(s) + 1);
	if (chaine == NULL)
		return (NULL);
	cpt = 0;
	while (s[cpt])
	{
		chaine[cpt] = (*f)(cpt, s[cpt]);
		cpt++;
	}
	chaine[cpt] = '\0';
	return (chaine);
}
