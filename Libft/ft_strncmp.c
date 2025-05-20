/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:17:48 by sbo               #+#    #+#             */
/*   Updated: 2023/11/11 19:42:14 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)

{
	size_t	cpt;

	if (n == 0)
		return (0);
	cpt = 0;
	while ((s1[cpt] == s2[cpt]) && (cpt < n - 1) && s1[cpt] && s2[cpt])
	{
		cpt++;
	}
	if ((unsigned char)s1[cpt] > (unsigned char)s2[cpt])
		return (1);
	else if ((unsigned char)s1[cpt] < (unsigned char)s2[cpt])
		return (-1);
	else
		return (0);
}
/*
int main (void)

{
	printf("%d\n",ft_strncmp("salu","salUt4",6));
	printf("%d",strncmp("SAlut5","SAlUt4",6));
}
*/
