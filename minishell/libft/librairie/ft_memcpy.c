/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:03:22 by dliuzzo           #+#    #+#             */
/*   Updated: 2023/11/13 13:26:04 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/libft.h"
#include "../includes/printf.h"
#include<stddef.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*d;
	char		*s;

	i = 0;
	if (dest == NULL && src == NULL)
	{
		return (NULL);
	}
	d = (char *)dest;
	s = (char *)src;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}	
/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void    *ft_memcpy(void *dest, const void *src, size_t n);

int main() {
	// Test 1
	char src1[] = "Hello, World!";
	char dest1[20];
	ft_memcpy(dest1, src1, strlen(src1) + 1);
	printf("Test 1: %s\n", dest1);

	// Test 2
	int src2[] = {1, 2, 3, 4, 5};
	int dest2[5];
	ft_memcpy(dest2, src2, sizeof(src2));
	printf("Test 2: ");
	for (size_t i = 0; i < sizeof(src2) / sizeof(src2[0]); i++) {
		printf("%d ", dest2[i]);
	}
	printf("\n");

	// Add more tests as needed

	return 0;
}
*/
