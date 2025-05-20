/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_digit_count_hexa.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 11:25:09 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/01/19 15:30:39 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/printf.h"

int	ft_digit_count_hexa(unsigned long long n, int base)
{
	int	digit;

	digit = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= base;
		digit++;
	}
	return (digit);
}
