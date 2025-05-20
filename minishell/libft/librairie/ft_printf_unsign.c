/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_unsign.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 11:25:39 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/01/25 15:51:53 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/printf.h"

unsigned int	ft_printf_unsign(va_list args)
{
	unsigned int	num;

	num = va_arg(args, unsigned int);
	ft_putnbr_unsigned(num);
	return (ft_digit_count_hexa((unsigned long long)num, 10));
}
