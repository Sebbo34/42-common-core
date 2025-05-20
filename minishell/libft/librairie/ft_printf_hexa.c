/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hexa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 11:25:25 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/01/25 15:51:37 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/printf.h"

int	ft_printf_hexa(va_list args, char c)
{
	unsigned int	hexa;

	hexa = va_arg(args, unsigned int);
	ft_putnbr_hexa(hexa, c);
	return (ft_digit_count_hexa(hexa, 16));
}
