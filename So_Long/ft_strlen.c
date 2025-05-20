/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 18:07:46 by seb               #+#    #+#             */
/*   Updated: 2024/01/24 14:03:16 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_strlen(const char *str)
{
	int	longueur;

	longueur = 0;
	if (!str)
		return (0);
	while (str[longueur] && str[longueur] != '\n')
	{
		longueur++;
	}
	return (longueur);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	cpt;

	cpt = 0;
	while ((s1[cpt] == s2[cpt]) && s1[cpt] && s2[cpt])
	{
		cpt++;
	}
	if ((unsigned char)s1[cpt] > (unsigned char)s2[cpt])
		return (1);
	else if ((unsigned char)s1[cpt] < (unsigned char)s2[cpt])
		return (-1);
	else
		return (0);
}

void	print_msg(int i)
{
	write(2, "Error\n", 6);
	if (i == 0)
		write(2, "Il n'y a pas assez d'argument\n", 30);
	if (i == 1)
		write(2, "Invalid fd\n", 11);
	if (i == 2)
		write(2, "La map n'est pas rectangle\n", 27);
	if (i == 3)
		write(2, "Invalid map\n", 12);
	if (i == 4)
		write(2, "La map n'est pas entoure de mur\n", 32);
	if (i == 5)
		write(2, "Il n'y a pas de chemin valide\n", 30);
	if (i == 6)
		write(2, "La carte n'est pas un .ber\n", 27);
}
