/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:41:47 by dliuzzo           #+#    #+#             */
/*   Updated: 2023/11/14 17:41:57 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/libft.h"
#include "../includes/printf.h"
#include<stddef.h>

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	if ((dst == NULL || src == NULL) && size == 0)
	{
		return (0);
	}
	if (size <= ft_strlen(dst))
		return (size + ft_strlen(src));
	i = ft_strlen(dst);
	while (src[j] && i < size - 1)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (i + ft_strlen(&src[j]));
}
/*
#include <stdio.h>
#include <string.h>

// Your ft_strlcat function here

int main() {
    // Test the ft_strlcat function
    char destination[13] = "Hello, ";
    const char *source = "World!";
    size_t destination_size = sizeof(destination);

    // Concatenate the source string to the destination string using ft_strlcat
    size_t result = ft_strlcat(destination, source, destination_size);

    printf("Concatenated String: %s\n", destination);
    printf("Result: %zu\n", result);

    return 0;
}
*/
