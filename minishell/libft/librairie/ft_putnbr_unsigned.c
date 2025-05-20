/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 11:26:37 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/01/25 15:52:40 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/printf.h"

void	ft_putnbr_unsigned(unsigned int nb)
{
	if (nb >= 10)
		ft_putnbr(nb / 10);
	ft_putchar(48 + (nb % 10));
}
