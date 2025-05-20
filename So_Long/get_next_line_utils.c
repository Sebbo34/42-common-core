/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 17:38:57 by sbo               #+#    #+#             */
/*   Updated: 2024/01/22 14:22:04 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*join_gnl(char *chaine, char *buffer, int j, int *i)
{
	char	*join;
	int		cpt;

	cpt = 0;
	if (j == 0)
		return (chaine);
	join = malloc (*i + j + 1);
	if (join == NULL)
		return (NULL);
	while (cpt < *i)
	{
		join [cpt] = chaine [cpt];
		cpt++;
	}
	cpt = 0;
	while (cpt < j)
	{
		join [*i + cpt] = buffer[cpt];
		cpt++;
	}
	join[*i + j] = 0;
	*i = *i + j;
	if (chaine != NULL)
		free(chaine);
	return (join);
}

char	*ft_strdup(char *chaine, int fin, int *i)

{
	char	*cpy;
	int		cpt;

	if (chaine == NULL)
		return (NULL);
	cpt = 0;
	cpy = malloc (fin + 2);
	if (cpy == NULL)
		return (NULL);
	*i = fin;
	while (cpt <= fin)
	{
		cpy [cpt] = chaine[cpt];
		cpt++;
	}
	cpy[cpt] = 0;
	return (cpy);
}

char	*ft_strdup_f(char *chaine, int fin)

{
	char	*cpy;
	int		cpt;

	if (chaine == NULL)
		return (NULL);
	fin = fin - 1;
	if (fin == -1)
		return (chaine);
	cpt = 0;
	cpy = malloc (fin + 2);
	if (cpy == NULL)
		return (NULL);
	while (cpt <= fin)
	{
		cpy [cpt] = chaine[cpt];
		cpt++;
	}
	cpy[cpt] = 0;
	if (chaine != NULL)
		free(chaine);
	return (cpy);
}

int	check_line(char *chaine, int i, int j)

{
	int	s;

	if (!chaine)
		return (0);
	s = i - j;
	if (s < 0)
		s = 0;
	while (s < i)
	{
		if (chaine [s] == '\n')
			return (1);
		s++;
	}
	return (0);
}
