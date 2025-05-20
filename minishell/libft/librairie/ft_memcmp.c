/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:31:36 by dliuzzo           #+#    #+#             */
/*   Updated: 2023/11/13 17:44:13 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/libft.h"
#include "../includes/printf.h"
#include<stddef.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*p1;
	const unsigned char	*p2;
	size_t				i;

	p1 = (const unsigned char *)s1;
	p2 = (const unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (*p1 == *p2 && ++i < n)
	{
		p1++;
		p2++;
	}
	return (*p1 - *p2);
}
/*
#include <stdio.h>
#include <string.h>

// Your memcmp function here

int main() {
    // Test the memcmp function
    const char *str1 = "Hello, World!";
    const char *str2 = "Hello, ";
    size_t len = strlen(str1);

    // Compare the first len characters of str1
    // and str2 using the memcmp function
    int result = memcmp(str1, str2, len);

    if (result == 0) {
        printf("Both strings are equal up to the first %zu characters.\n"
	, len);
    } else if (result < 0) {
        printf("str1 is less than str2.\n");
    } else {
        printf("str1 is greater than str2.\n");
    }

    return 0;
}
*/
