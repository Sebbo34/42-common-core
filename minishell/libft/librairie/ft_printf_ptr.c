/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 11:25:31 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/01/25 15:51:50 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/printf.h"

int	ft_printf_ptr(va_list args, char flag)
{
	uintptr_t	ptr;

	ptr = va_arg(args, uintptr_t);
	if (ptr == 0)
		return ((int)write(1, "(nil)", 5));
	else
		write(1, "0x", 2);
	ft_putnbr_hexa(ptr, flag);
	return (ft_digit_count_hexa((unsigned long long)ptr, 16) + 2);
}
