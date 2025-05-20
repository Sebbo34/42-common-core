/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 19:27:39 by sbo               #+#    #+#             */
/*   Updated: 2023/11/11 19:35:49 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	chevauchement(void *dest, const void *src, size_t n)

{
	size_t	cpt;

	cpt = 0;
	while (cpt <= n)
	{
		if (src + cpt == dest)
			return (cpt);
		cpt++;
	}
	cpt = 0;
	while (cpt <= n)
	{
		if (dest + cpt == src)
			return (-cpt);
		cpt++;
	}
	return (0);
}

void	*ft_memmove(void *dest, const void *src, size_t size)

{
	size_t			cpt;
	unsigned char	*d;
	unsigned char	*s;

	if (dest == NULL && src == NULL)
		return (NULL);
	d = (unsigned char *) dest;
	s = (unsigned char *) src;
	cpt = 0;
	if (chevauchement(dest, src, size) > 0)
	{
		while (size > 0)
		{
			d[size - 1] = s[size - 1];
			size--;
		}
	}
	else
	{
		cpt = -1;
		while (++cpt < size)
			d[cpt] = s[cpt];
	}
	return (dest);
}
