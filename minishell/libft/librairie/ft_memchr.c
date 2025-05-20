/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:42:34 by dliuzzo           #+#    #+#             */
/*   Updated: 2023/11/13 16:33:17 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/libft.h"
#include "../includes/printf.h"
#include<stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*p;

	p = s;
	while (n > 0)
	{
		if (*p == (unsigned char)c)
		{
			return ((void *)p);
		}
		p++;
		n--;
	}
	return (NULL);
}
/*
#include <stdio.h>
#include <string.h>

// Your ft_memchr function here

int main() {
    // Test case 1: Search for 'A' in the string "Hello, World!"
    const char str1[] = "Hello, World!";
    char target1 = 'A';
    size_t size1 = strlen(str1);
    void *result1 = ft_memchr(str1, target1, size1);

    if (result1 != NULL) {
        printf("Test 1: Found '%c' at position %ld\n"
	, target1, (char *)result1 - str1);
    } else {
        printf("Test 1: '%c' not found in the string\n", target1);
    }

    // Test case 2: Search for 'o' in the string "Hello, World!"
    const char str2[] = "Hello, World!";
    char target2 = 'o';
    size_t size2 = strlen(str2);
    void *result2 = ft_memchr(str2, target2, size2);

    if (result2 != NULL) {
        printf("Test 2: Found '%c' at position %ld\n"
	, target2, (char *)result2 - str2);
    } else {
        printf("Test 2: '%c' not found in the string\n", target2);
    }

    // Test case 3: Search for 'z' in the string "Hello, World!"
    const char str3[] = "Hello, World!";
    char target3 = 'z';
    size_t size3 = strlen(str3);
    void *result3 = ft_memchr(str3, target3, size3);

    if (result3 != NULL) {
        printf("Test 3: Found '%c' at position %ld\n"
	, target3, (char *)result3 - str3);
    } else {
        printf("Test 3: '%c' not found in the string\n", target3);
    }

    return 0;
}
*/
