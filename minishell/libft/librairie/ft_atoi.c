/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:29:31 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/01/19 15:29:37 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/printf.h"

static void	ft_error(char **tab, t_stack *sa)
{
	write(2, "Error\n", 6);
	ft_lstiter(&sa, free);
}

int	ft_atoi(char *nptr, char **tab, t_stack sa)
{
	int					i;
	unsigned long long	r;
	int					m;

	i = 0;
	r = 0;
	m = 1;
	while (nptr[i] && ((nptr[i] >= '\t' && nptr[i] <= '\r') || nptr[i] == ' '))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			m = -1;
		i++;
	}
	while (nptr[i] - '0' >= 0 && nptr[i] - '0' <= 9)
	{
		r = 10 * r + (nptr[i] - '0');
		i++;
		if ((r > 2147483647 && m == 1) || (r > 2147483648 && m == -1))
			ft_error(tab, sa);
	}
	if (i == 0 || i != (int)ft_strlen(nptr))
		ft_error(tab, sa);
	return ((int)r * m);
}
/*
#include <stdio.h>

int	main(void)
{
	char	*str;
	char	*str1;
	char	*str2;
	char	*str3;
	char	*str4;

	str = "-123r4";
	str1 = "+123r4";
	str2 = "  +123r4";
	str3 = "  --123r4";
	str4 = "  - 123r4";
	printf("%i\n",ft_atoi(str));
	printf("%i\n",ft_atoi(str1));
	printf("%i\n",ft_atoi(str2));
	printf("%i\n",ft_atoi(str3));
	printf("%i\n",ft_atoi(str4));
}
*/
