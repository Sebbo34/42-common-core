/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 08:47:15 by sbo               #+#    #+#             */
/*   Updated: 2024/01/16 14:26:58 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_strlen(const char *str)

{
	size_t	longueur;

	longueur = 0;
	while (str[longueur])
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

int	ft_strncmp(const char *s1, const char *s2, size_t n)

{
	size_t	cpt;

	if (n == 0)
		return (0);
	cpt = 0;
	while ((s1[cpt] == s2[cpt]) && (cpt < n - 1) && s1[cpt] && s2[cpt])
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
