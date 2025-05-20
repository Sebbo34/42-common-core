/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:16:03 by dliuzzo           #+#    #+#             */
/*   Updated: 2023/11/13 14:04:13 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/libft.h"
#include "../includes/printf.h"

#include <stddef.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (!big || !little)
		return (NULL);
	if (!little || !little[0])
		return ((char *)big);
	i = 0;
	while (big[i] && i < len)
	{
		j = 0;
		while (big[i + j] && little[j]
			&& i + j < len && big[i + j] == little[j])
			j++;
		if (!little[j])
			return ((char *)(big + i));
		i++;
	}
	return (NULL);
}
/*
int main()
{
    // Test 1
    char big1[] = "Hello, World!";
    char little1[] = "World";
    char *result1 = ft_strnstr(big1, little1, sizeof(big1));

    if (result1 != NULL)
    {
        printf("Test 1:\nBig: %s\nLittle: %s\nResult: %s\n\n"
	, big1, little1, result1);
    }
    else
    {
        printf("Test 1: Substring not found.\n\n");
    }

    // Test 2
    char big2[] = "This is a simple test.";
    char little2[] = "simple";
    char *result2 = ft_strnstr(big2, little2, sizeof(big2));

    if (result2 != NULL)
    {
        printf("Test 2:\nBig: %s\nLittle: %s\nResult: %s\n\n",
       	big2, little2, result2);
    }
    else
    {
        printf("Test 2: Substring not found.\n\n");
    }

    // Test 3
    char big3[] = "ABCDEF";
    char little3[] = "XYZ";
    char *result3 = ft_strnstr(big3, little3, sizeof(big3));

    if (result3 != NULL)
    {
        printf("Test 3:\nBig: %s\nLittle: %s\nResult: %s\n\n",
       	big3, little3, result3);
    }
    else
    {
        printf("Test 3: Substring not found.\n\n");
    }

    return 0;
}
*/
