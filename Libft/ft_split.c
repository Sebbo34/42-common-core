/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:55:49 by sbo               #+#    #+#             */
/*   Updated: 2023/11/11 19:47:40 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_word(char const *s, char c)
{
	int	cpt;
	int	nbr_mot;

	nbr_mot = 0;
	cpt = 0;
	if (s[0] == 0)
	{
		return (0);
	}
	while (s[cpt] == c)
	{
		cpt++;
	}
	while (s[cpt])
	{
		if (s[cpt] == c || s[cpt + 1] == '\0')
		{
			if (s[cpt + 1] != c || s[cpt + 1] == '\0')
				nbr_mot++;
		}
		cpt++;
	}
	return (nbr_mot);
}

static int	count_ltr(char const *s, char c, int ind)

{
	int	i_j_n[3];

	i_j_n[0] = 0;
	i_j_n[1] = 0;
	i_j_n[2] = 0;
	if (c == 0)
		return (ft_strlen(s));
	while (s[i_j_n[0]] == c)
		i_j_n[0]++;
	while (s[i_j_n[0]])
	{
		if (s[i_j_n[0]] != c)
			i_j_n[1]++;
		if (s[i_j_n[0]] == c || (s[i_j_n[0] + 1] == '\0'))
		{
			if (i_j_n[2] == ind)
				return (i_j_n[1]);
			else
				i_j_n[1] = 0;
			if (s[i_j_n[0] + 1] != c || s[i_j_n[0] + 1] == '\0')
				i_j_n[2]++;
		}
		i_j_n[0]++;
	}
	return (i_j_n[1]);
}

static void	free_tab(char **tab, int nbr_mot)

{
	int	i;

	i = 0;
	while (i < nbr_mot)
	{
		free (tab[i]);
		i++;
	}
	free(tab);
}

char	**ft_split(char const *s, char c)

{
	char	**tab;
	int		cpt;
	int		nbr_mot;

	if (s == NULL)
		return (NULL);
	cpt = 0;
	nbr_mot = -1;
	tab = (char **) malloc(sizeof(char *) * (count_word(s, c) + 1));
	if (tab == NULL)
		return (NULL);
	while (++nbr_mot < count_word(s, c))
	{
		while (s[cpt] == c)
			cpt++;
		tab[nbr_mot] = ft_substr(s, cpt, count_ltr(s, c, nbr_mot));
		if (tab [nbr_mot] == NULL)
		{
			free_tab(tab, nbr_mot);
			return (NULL);
		}
		cpt = cpt + count_ltr(s, c, nbr_mot);
	}
	tab[nbr_mot] = NULL;
	return (tab);
}
/*
int main(void)

{
	char **tab;
	char chaine [] = "--1-2--3---4----5-----42-";
	//printf("%s\n",ft_substr(chaine,16,4));

	
	tab = ft_split(chaine,'-');
	int i = 0;
	while(i < 5 )
	{
		printf("%s\n",tab[5]);
		i++;
	}
	
}
*/