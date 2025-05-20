/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:42:46 by dliuzzo           #+#    #+#             */
/*   Updated: 2023/11/13 16:09:22 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/libft.h"
#include "../includes/printf.h"

#include <stddef.h>

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	if (s == NULL || f == NULL)
		return ;
	while (s[i] != '\0')
	{
		f(i, &s[i]);
		i++;
	}
}
/*
#include <ctype.h>
#include <stdio.h>
void dummy_function(unsigned int index, char *character)
{
    // Convert the character to uppercase
    (void) index;
    *character = toupper(*character);
}

int main(void)
{
    // Test with a string
    char testString[] = "Hello, World!";

    // Call ft_striteri with the dummy_function
    ft_striteri(testString, &dummy_function);

    // Print the modified string
    printf("Modified String: %s\n", testString);

    return 0;
}
*/
