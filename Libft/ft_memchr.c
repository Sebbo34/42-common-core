/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 18:00:28 by sbo               #+#    #+#             */
/*   Updated: 2023/11/11 18:00:37 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)

{
	unsigned char	*ptr;
	size_t			cpt;

	cpt = 0;
	ptr = (unsigned char *)s;
	c = (unsigned char)c;
	while (cpt < n)
	{
		if (*ptr == c)
			return (ptr);
		ptr++;
		cpt++;
	}
	return (NULL);
}
