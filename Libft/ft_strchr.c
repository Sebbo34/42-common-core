/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:33:59 by sbo               #+#    #+#             */
/*   Updated: 2023/11/11 19:39:17 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)

{
	int	cpt;

	cpt = 0;
	c = (unsigned char)c;
	if (c == 0)
	{
		return ((char *)s + ft_strlen(s));
	}
	while (s[cpt])
	{
		if (s[cpt] == c)
		{
			return ((char *)&s[cpt]);
		}
		cpt++;
	}
	return (NULL);
}
/*
int main (void)

{
	char chaine[] = "123";
	char *ptr;
	printf("%p\n" , ft_strchr(chaine,'v'));
	printf("%p\n", chaine + 2);
}
*/