/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 17:20:31 by dliuzzo           #+#    #+#             */
/*   Updated: 2023/11/13 13:50:32 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/libft.h"
#include "../includes/printf.h"
#include <stdlib.h>
#include <stddef.h>

char	*ft_strdup(const char *s)
{
	int		i;
	char	*ptr;

	i = ft_strlen(s);
	ptr = (char *)malloc((i + 1) * sizeof (char));
	if (ptr == NULL)
	{
		return (0);
	}
	i = 0;
	while (s[i] != '\0')
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
/*
int main()
{
    // Test 1
    char source1[] = "Hello, World!";
    char *result1 = ft_strdup(source1);

    if (result1 != NULL)
    {
        printf("Test 1:\nOriginal: %s\nDuplicate: %s\n\n", source1, result1);
        free(result1);
    }
    else
    {
        printf("Test 1: Memory allocation failed.\n\n");
    }

    // Test 2
    char source2[] = "houdini";
    char *result2 = ft_strdup(source2);

    if (result2 != NULL)
    {
        printf("Test 2:\nOriginal: %s\nDuplicate: %s\n\n", source2, result2);
        free(result2);
    }
    else
    {
        printf("Test 2: Memory allocation failed.\n\n");
    }

    // Add more tests as needed

    return 0;
}
*/
