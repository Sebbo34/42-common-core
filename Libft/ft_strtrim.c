/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 15:00:43 by seb               #+#    #+#             */
/*   Updated: 2023/11/11 19:04:14 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	verif(char c, char const *set)

{
	int	cpt;

	cpt = 0;
	while (set[cpt])
	{
		if (set[cpt] == c)
			return (1);
		cpt++;
	}
	return (0);
}

static int	ft_debut( char const *s1, char const *set)

{
	int	debut;

	debut = 0;
	while (verif(s1[debut], set) == 1)
		debut++;
	return (debut);
}

static int	ft_fin( char const *s1, char const *set)

{
	int	fin;

	fin = ft_strlen(s1) - 1;
	while (verif(s1[fin], set) == 1)
		fin--;
	return (fin);
}

char	*ft_strtrim(char const *s1, char const *set)

{
	int		debut;
	int		fin;
	int		cpt;
	char	*chaine;

	if (s1 == NULL)
		return (NULL);
	cpt = 0;
	debut = ft_debut(s1, set);
	fin = ft_fin(s1, set);
	if (fin - debut >= 0)
		chaine = malloc((fin - debut) + 2);
	else
		chaine = malloc(1);
	if (chaine == NULL)
		return (NULL);
	while (fin >= debut)
	{
		chaine [cpt] = s1[debut];
		cpt++;
		debut++;
	}
	chaine [cpt] = '\0';
	return (chaine);
}
