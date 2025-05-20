/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 11:25:42 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/01/25 15:49:25 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/printf.h"

static int	check_convert(char c, va_list args)
{
	int	count;

	count = 0;
	if (c == 'c')
		count += ft_printf_char(args);
	else if (c == 's')
		count += ft_printf_str(args);
	else if (c == 'u')
		count += ft_printf_unsign(args);
	else if (c == 'x' || c == 'X')
		count += ft_printf_hexa(args, c);
	else if (c == 'p')
		count += ft_printf_ptr(args, c);
	else if (c == 'd' || c == 'i')
		count += ft_printf_int(args);
	else if (c == '%')
		return ((int)write(1, "%", 1));
	else
		count = -1;
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;

	if (format == NULL)
		return (-1);
	count = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format != '%')
			count += write(1, &*format, 1);
		else if (*format == '%')
		{
			count += check_convert(*(format + 1), args);
			format++;
		}
		format++;
	}
	va_end(args);
	return (count);
}

// #include<stdio.h>
// int	main(void)
// {
// 	int count;
// 	int countp;
// 	int i;
// 	// unsigned int ui;
// 	// char c = 'c';
// 	// char *str;
// 	i = -123;
// 	// ui = 0;
// 	// str = "";
// 	// count = 0;
// 	count = ft_printf("ft_printf int %x \n", i);
// 	countp = printf("printf int %x \n", i);
// 	ft_printf("\n %i", count);
// 	printf("\n %i", countp);
// 	return (0);
// }
