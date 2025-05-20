/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:13:12 by dliuzzo           #+#    #+#             */
/*   Updated: 2023/11/15 14:28:51 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/libft.h"
#include "../includes/printf.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*fullbish;
	size_t	new;

	if (s == NULL)
		return (NULL);
	if ((unsigned int)ft_strlen(s) < start)
		return (ft_strdup(""));
	new = ft_strlen(s + start);
	if (new < len)
		len = new;
	fullbish = (char *)malloc((len + 1) * sizeof(char));
	if (fullbish == NULL)
		return (NULL);
	ft_strlcpy(fullbish, s + start, len + 1);
	return (fullbish);
}
/*
#include <stdio.h>
#include <assert.h>
#include <string.h>
int main(void)
{
    // Test 1: Chaîne non nulle, extrait une sous-chaîne
    const char *input1 = "Hello, World!";
    char *result1 = ft_substr(input1, 7, 5);
    assert(strcmp(result1, "World") == 0);
    free(result1);

    // Test 2: Chaîne non nulle, début hors de la plage, retourne une chaîne vide
    const char *input2 = "Hello, World!";
    char *result2 = ft_substr(input2, 15, 5);
    assert(strcmp(result2, "") == 0);
    free(result2);

    // Test 3: Chaîne NULL, doit retourner NULL
    const char *input3 = NULL;
    char *result3 = ft_substr(input3, 0, 5);
    assert(result3 == NULL);

    // Test 4: Chaîne vide, doit retourner une chaîne vide
    const char *input4 = "";
    char *result4 = ft_substr(input4, 0, 5);
    assert(strcmp(result4, "") == 0);
    free(result4);

    // Ajoutez d'autres tests au besoin...

    printf("Tous les tests ont réussi!\n");

    return 0;
}
*/
