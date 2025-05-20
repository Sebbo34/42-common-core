/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:54:38 by sbo               #+#    #+#             */
/*   Updated: 2024/02/15 17:41:42 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(char *nptr)
{
	int	cpt;
	int	nbr;
	int	verif;

	verif = 0;
	nbr = 0;
	cpt = 0;
	if (nptr[cpt] == '-')
		return (-2);
	while (nptr[cpt] >= '0' && nptr[cpt] <= '9' )
	{
		verif++;
		nbr = nbr * 10 + nptr[cpt] - '0';
		cpt++;
	}
	if ((nptr[cpt] < '0' || nptr[cpt] > '9') && nptr[cpt])
		verif = 0;
	if (verif == 0 || (verif > 10) || (verif == 10 && nptr[0] > '3'))
		return (-2);
	return (nbr);
}

/* 
#include <stdio.h>
int main (void)

{
	printf("atoi = %d",ft_atoi("21474836477789"));

}
 */