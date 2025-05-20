/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manage.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 17:18:06 by sbo               #+#    #+#             */
/*   Updated: 2023/12/13 17:33:23 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_isnum(char **argv, int argc)

{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		if (argv[i][j] == '-')
			j++;
		if (!argv[i][j])
			return (0);
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

char	ft_isint(char *nptr)

{
	long	cpt;
	long	nbr;
	long	negatif;

	nbr = 0;
	cpt = 0;
	negatif = 1;
	if (nptr[cpt] == '+' || nptr[cpt] == '-' )
	{
		if (nptr[cpt] == '-')
				negatif = -1;
		cpt++;
	}
	while (nptr[cpt] >= '0' && nptr[cpt] <= '9' )
	{
		nbr = nbr * 10 + nptr[cpt] - '0';
		cpt++;
	}
	if (nbr < -2147483648 || nbr > 2147483647 || cpt > 12)
		return ('n');
	return ('y');
}

int	ft_checkint(char **argv, int argc)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (ft_isint(argv[i]) == 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_isonly(t_pile *stack)

{
	t_pile	*temp;

	temp = stack;
	while (stack -> next)
	{
		temp = stack -> next;
		while (temp)
		{
			if (stack -> nbr == temp -> nbr)
			{
				write (2, "Error\n", 6);
				return (0);
			}
			temp = temp -> next;
		}
		stack = stack -> next;
	}
	return (1);
}

int	error_manage(char **argv, int argc)

{
	if (ft_isnum(argv, argc) == 0)
	{
		write (2, "Error\n", 6);
		return (0);
	}
	if (ft_checkint(argv, argc) == 0)
	{
		write (2, "Error\n", 6);
		return (0);
	}
	return (1);
}
