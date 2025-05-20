/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:05:27 by dliuzzo           #+#    #+#             */
/*   Updated: 2023/11/13 18:30:01 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/libft.h"
#include "../includes/printf.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	else
		return (0);
}
/*
#include<stdio.h>
int main(void)
{
	printf("%i\n", ft_isprint(32));
	printf("%i\n", ft_isprint(12));
	printf("%i\n", ft_isprint(132));
}
*/
