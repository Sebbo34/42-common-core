/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_affiche.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 18:56:54 by sbo               #+#    #+#             */
/*   Updated: 2023/11/22 13:09:20 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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

int	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
	return (1);
}

int	ft_putstr_fd(char *s, int fd)

{
	int	cpt;

	if (s == NULL)
	{
		ft_putstr_fd("(null)", 1);
		return (6);
	}
	cpt = 0;
	while (s[cpt])
	{
		cpt++;
	}
	write(fd, s, cpt);
	return (cpt);
}

int	ft_putnbr_fd(int n)
{
	int		j;
	char	*chaine;

	chaine = ft_itoa(n);
	if (chaine == NULL)
		return (0);
	j = ft_strlen(chaine);
	ft_putstr_fd(chaine, 1);
	free(chaine);
	return (j);
}
