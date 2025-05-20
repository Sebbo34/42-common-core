/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 11:25:36 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/01/09 17:48:58 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/printf.h"

int	ft_printf_str(va_list args)
{
	char	*str;
	int		len;

	str = va_arg(args, char *);
	len = 0;
	if (str == NULL)
		return (write(1, "(null)", 6));
	while (str[len] != '\0')
	{
		write(1, &str[len], 1);
		len++;
	}
	return (len);
}
