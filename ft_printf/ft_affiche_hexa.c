/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_affiche_hexa.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 18:54:29 by sbo               #+#    #+#             */
/*   Updated: 2023/11/22 12:49:17 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	base_hexa(unsigned long long nbr)

{
	int	i;

	if (nbr == 0)
		return (1);
	i = 0;
	while (nbr > 0)
	{
		nbr = nbr / 16;
		i++;
	}
	return (i);
}

static unsigned long long	pui(int nbr, int p)
{
	unsigned long long	temp;
	int					i;

	i = 0;
	temp = 1;
	while (i < p)
	{
		temp = temp * nbr;
		i++;
	}
	return (temp);
}

int	ft_affiche_hexa( unsigned int nbr, char *base)
{
	int		i;
	int		j;
	char	*chaine;

	i = base_hexa(nbr);
	j = 0;
	chaine = malloc (base_hexa(nbr) + 1);
	if (chaine == NULL)
		return (0);
	while (j < i)
	{
		chaine [j] = base [nbr / pui(16, i - j - 1)];
		nbr = nbr % pui(16, i - j - 1);
		j++;
	}
	chaine [j] = 0;
	ft_putstr_fd(chaine, 1);
	j = ft_strlen(chaine);
	free(chaine);
	return (j);
}

int	aff_p(unsigned long long nbr, char *base)
{
	int		i;
	int		j;
	char	*chaine;

	if (nbr == 0)
	{
		ft_putstr_fd("(nil)", 1);
		return (5);
	}
	write(1, "0x", 2);
	i = base_hexa(nbr);
	j = -1;
	chaine = malloc (base_hexa(nbr) + 1);
	if (chaine == NULL)
		return (0);
	while (j++ < i)
	{
		chaine [j] = base [nbr / pui(16, i - j - 1)];
		nbr = nbr % pui(16, i - j - 1);
	}
	chaine [j - 1] = 0;
	ft_putstr_fd(chaine, 1);
	j = ft_strlen(chaine);
	free(chaine);
	return (j + 2);
}
