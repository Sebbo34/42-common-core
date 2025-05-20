/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:01:12 by dliuzzo           #+#    #+#             */
/*   Updated: 2023/11/06 12:10:44 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/libft.h"
#include "../includes/printf.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}
/*
#include <stdio.h>

int main()
{
        int c;

	char result;

     c = '*';
        result = ft_isdigit(c);
     printf("The result is %d\n", result);

     c = 'g';
        result = ft_isdigit(c);
     printf("The result is %d\n", result);

     c = '2';
        result = ft_isdigit(c);
     printf("The result is %d\n", result);

        return 0;
}
*/
