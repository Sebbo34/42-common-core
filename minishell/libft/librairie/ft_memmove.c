/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:56:30 by dliuzzo           #+#    #+#             */
/*   Updated: 2023/11/14 12:53:20 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/libft.h"
#include "../includes/printf.h"
#include <string.h>

char	*cpy(char *d1, const char *s1, size_t n1)
{
	size_t	i;

	i = 0;
	if (d1 < s1)
	{
		while (i < n1)
		{
			d1[i] = s1[i];
			i++;
		}
	}
	else
	{
		i = n1 - 1;
		while (i > 0)
		{
			d1[i] = s1[i];
			i--;
		}
		d1[i] = s1[i];
	}
	return (d1);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*d;
	const char	*s;

	d = (char *)dest;
	s = (const char *)src;
	if (d == s || n == 0)
		return (dest);
	dest = cpy(d, s, n);
	return (dest);
}
/*
int main(void)
{
    char source[] = "Hello, World!";
    char destination[20];

    // Copy the first 5 characters from source to destination using ft_memmove
    ft_memmove(destination, source, 1);

    // Print the result
    printf("Destination: %s\n", destination);

    return 0;
}
*/
