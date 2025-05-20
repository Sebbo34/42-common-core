/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:11:56 by dliuzzo           #+#    #+#             */
/*   Updated: 2023/11/13 13:12:44 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/libft.h"
#include "../includes/printf.h"

int	ft_isalnum(int c)
{
	if ((c >= 48 && c <= 57) || ((c >= 65 && c <= 90) || (c >= 97 && c <= 122)))
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

     c = 49;
        result = ft_isalnum(c);
     printf("The result is %d\n", result);

     c = 'g';
        result = ft_isalnum(c);
     printf("The result is %d\n", result);

     c = '+';
        result = ft_isalnum(c);
     printf("The result is %d\n", result);

        return 0;
}
*/
