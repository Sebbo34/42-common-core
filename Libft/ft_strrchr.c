/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:56:49 by sbo               #+#    #+#             */
/*   Updated: 2023/11/11 19:40:45 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)

{
	int	cpt;
	int	temp;
	int	verify;

	cpt = 0;
	verify = 0;
	c = (unsigned char)c;
	while (s[cpt])
	{
		if (s[cpt] == c)
		{
			temp = cpt;
			verify = 1;
		}
		cpt++;
	}
	if (c == 0)
		return ((char *) &s[cpt]);
	if (verify == 1)
		return ((char *) &s[temp]);
	else
		return (NULL);
}
