/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 15:29:15 by sbo               #+#    #+#             */
/*   Updated: 2023/11/28 11:06:58 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	affiche_type(char c, va_list lst)

{
	int	i;

	if (c == 's')
		return (ft_putstr_fd((char *)va_arg(lst, char *), 1));
	if (c == 'd')
		return (ft_putnbr_fd((int)va_arg(lst, int)));
	if (c == 'c')
		return (ft_putchar_fd((char) va_arg(lst, int), 1));
	if (c == 'p')
	{
		i = aff_p((unsigned long long) va_arg(lst, int *), "0123456789abcdef");
		return (i);
	}
	if (c == 'x')
		return (ft_affiche_hexa ((int)va_arg(lst, int), "0123456789abcdef"));
	if (c == 'X')
		return (ft_affiche_hexa ((int)va_arg(lst, int), "0123456789ABCDEF"));
	if (c == 'i')
		return (ft_putnbr_fd((int)va_arg(lst, int)));
	if (c == 'u')
		return (ft_uputnbr((int)va_arg(lst, int)));
	return (0);
}

int	affiche_chaine(const char *format, va_list lst)

{
	int	i;
	int	somme;

	i = 0;
	somme = 0;
	while (format[i])
	{
		if (format [i] == '%' && format[i + 1] != '%')
		{
			i++;
			somme = somme + affiche_type(format[i], lst) - 1;
		}
		else if (format [i] == '%' && format[i + 1] == '%')
		{
			i++;
			ft_putchar_fd ('%', 1);
		}
		else
			ft_putchar_fd(format[i], 1);
		somme++;
		i++;
	}
	return (somme);
}

int	ft_printf( const char *format, ...)

{
	va_list	lst;
	int		somme;

	if (!format)
		return (-1);
	va_start (lst, format);
	somme = affiche_chaine(format, lst);
	va_end(lst);
	return (somme);
}

/*  int main (void)
{
	int* i = 0;
	//printf("\n%d\n",printf("%p\n%s",&i,"5"));
	printf("\n%d\n",ft_printf("%p\n%s",&i,"5"));
	//affiche_hexa(  ptr,"0123456789abcdef");
	printf ("%d",ft_printf(0));
	printf ("%d",printf(0));
} */