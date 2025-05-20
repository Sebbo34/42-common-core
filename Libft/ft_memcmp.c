/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 21:22:31 by seb               #+#    #+#             */
/*   Updated: 2023/11/11 18:40:18 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*ptr;
	unsigned char	*ptr2;
	size_t			cpt;

	cpt = 0;
	ptr = (unsigned char *) s1;
	ptr2 = (unsigned char *) s2;
	while (cpt < n)
	{
		if (ptr[cpt] != ptr2[cpt])
			return (ptr[cpt] - ptr2[cpt]);
		cpt++;
	}
	return (0);
}
