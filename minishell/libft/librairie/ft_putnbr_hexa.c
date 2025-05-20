/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hexa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 11:26:33 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/01/25 15:52:32 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/printf.h"

void	ft_putnbr_hexa(unsigned long long n, char c)
{
	char	*hex_digit;

	if (c == 'x' || c == 'p')
		hex_digit = "0123456789abcdef";
	else
		hex_digit = "0123456789ABCDEF";
	if (n >= 16)
		ft_putnbr_hexa(n / 16, c);
	ft_putchar(hex_digit[n % 16]);
}
