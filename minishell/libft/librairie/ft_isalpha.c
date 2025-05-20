/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:39:01 by dliuzzo           #+#    #+#             */
/*   Updated: 2023/11/06 12:35:42 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/libft.h"
#include "../includes/printf.h"

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	else
		return (0);
}	
/*
#include <stdio.h>

int main()
{
 	char c, result;

     c = '*';
  	result = ft_isalpha(c);
     printf("The result is %d\n", result);

     c = 'g';
  	result = ft_isalpha(c);
     printf("The result is %d\n", result);

     c = '+';
  	result = ft_isalpha(c);
     printf("The result is %d\n", result);

  	return 0;
}
*/
