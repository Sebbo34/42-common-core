/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 11:25:22 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/01/25 15:50:44 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/printf.h"

int	ft_printf_char(va_list args)
{
	int	c;

	c = va_arg(args, int);
	return (write(1, &c, 1));
}
