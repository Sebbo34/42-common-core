/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:13:50 by dliuzzo           #+#    #+#             */
/*   Updated: 2023/11/13 17:22:47 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/libft.h"
#include "../includes/printf.h"
#include <stdlib.h>
#include<unistd.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int		i;
	unsigned int		j;
	char				*fullbish;

	i = 0;
	if (s == NULL || f == NULL)
		return (NULL);
	while (s[i])
		i++;
	fullbish = (char *)malloc((i + 1) * sizeof(char));
	if (fullbish == NULL)
		return (NULL);
	j = 0;
	while (j < i)
	{
		fullbish[j] = f(j, s[j]);
		j++;
	}
	fullbish[i] = '\0';
	return (fullbish);
}
/*
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Your ft_strmapi function here

char uppercase_mapping(unsigned int index, char c) {
	(void) index;
    if (c >= 'a' && c <= 'z') {
        return c - 'a' + 'A';
    }
    return c;
}

int main() {
    // Test the ft_strmapi function with uppercase_mapping
    const char *inputString = "Hello, World!";

    // Map each character to uppercase using the uppercase_mapping function
    char *result = ft_strmapi(inputString, &uppercase_mapping);

    if (result != NULL) {
        printf("Original String: %s\n", inputString);
        printf("Mapped String  : %s\n", result);
        free(result); // Don't forget to free the allocated memory
    } else {
        printf("Memory allocation failure.\n");
    }

    return 0;
}
*/
