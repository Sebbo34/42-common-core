/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 20:19:41 by seb               #+#    #+#             */
/*   Updated: 2023/11/21 17:10:13 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	cpt;
	size_t	lenght;
	char	*chaine;

	lenght = ft_strlen(src);
	cpt = 0;
	chaine = (char *)src;
	if (dstsize == 0)
		return (lenght);
	while (src[cpt] && cpt < dstsize - 1)
	{
		dst[cpt] = chaine[cpt];
		cpt++;
	}
	dst[cpt] = '\0';
	return (lenght);
}
/*
int main (void)

{
	printf("%d",123);
}
*/