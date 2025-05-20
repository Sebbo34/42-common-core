/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 17:55:27 by sbo               #+#    #+#             */
/*   Updated: 2023/11/11 17:56:37 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	cpt;
	size_t	len_d;
	size_t	len_s;

	if ((!dest || !src) && size == 0)
		return (0);
	cpt = 0;
	len_d = ft_strlen(dest);
	len_s = ft_strlen(src);
	if (len_d >= size)
	{
		return (size + len_s);
	}
	while ((len_d < size - 1) && src[cpt])
	{
		dest[len_d] = src[cpt];
		len_d++;
		cpt++;
	}
	dest[len_d] = '\0';
	return (ft_strlen(dest) + ft_strlen(&src[cpt]));
}
/*
int main(void)

{
	char chaine[12] = "salut";

	printf("%lu\n",strlcat(chaine,"C452",4));
	printf("%s\n",chaine);
	printf("%p\n",chaine);
	printf("%p\n",chaine + 5);
	printf("%c\n",*(chaine + 4));
}
*/