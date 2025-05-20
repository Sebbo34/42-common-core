/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:26:58 by sbo               #+#    #+#             */
/*   Updated: 2023/11/21 18:22:07 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	basedix(long n)

{
	int	cpt;

	cpt = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n = n / 10;
		cpt++;
	}
	return (cpt);
}

static void	puttab(long n, char *chaine, int *ptr)
{
	if (n == -2147483648)
	{
		ft_strlcpy(chaine, "-2147483648", 12);
	}
	else
	{
		if (n < 0)
		{
			chaine[*ptr] = '-';
			n = -1 * n;
			*ptr = *ptr + 1;
		}
		if (n >= 10)
		{
			puttab(n / 10, chaine, ptr);
			chaine[*ptr] = '0' + n % 10;
			*ptr = *ptr + 1;
		}
		else
		{
			chaine[*ptr] = '0' + n % 10;
			*ptr = *ptr + 1;
		}
	}
}

char	*ft_itoa(long n)

{
	int		base;
	char	*chaine;
	int		i;

	i = 0;
	if (n < 0)
	{
		base = basedix(-n) + 1;
		if (n == -2147483648)
			base = 11;
	}
	else
		base = basedix(n);
	chaine = malloc(base + 1);
	if (chaine == NULL)
		return (NULL);
	puttab(n, chaine, &i);
	if (n != -2147483648)
		chaine [base] = '\0';
	return (chaine);
}
