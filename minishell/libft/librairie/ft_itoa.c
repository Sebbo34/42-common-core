/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 15:25:52 by dliuzzo           #+#    #+#             */
/*   Updated: 2023/11/14 12:16:39 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/libft.h"
#include "../includes/printf.h"
#include <stdlib.h>
#include<unistd.h>

static int	len(long n)
{
	int	count;

	count = 0;
	if (n == 0)
		count++;
	if (n < 0)
	{
		n *= -1;
		count++;
	}
	while (n > 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*yasciified;
	int		i;
	long	nbr;

	nbr = n;
	i = len(nbr);
	yasciified = malloc((sizeof(char) * (i + 1)));
	if (!yasciified)
		return (0);
	yasciified[i--] = '\0';
	if (nbr < 0)
	{
		yasciified[0] = '-';
		nbr *= -1;
	}
	if (nbr == 0)
		yasciified[0] = '0';
	while (nbr > 0)
	{
		yasciified[i] = nbr % 10 + '0';
		nbr /= 10;
		i--;
	}
	return (yasciified);
}
