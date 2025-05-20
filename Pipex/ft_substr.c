/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:20:40 by sbo               #+#    #+#             */
/*   Updated: 2024/01/03 13:07:07 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)

{
	char	*chaine;
	size_t	cpt;

	if (s == NULL)
		return (NULL);
	cpt = 0;
	if (start + len > ft_strlen(s))
		len = ft_strlen (s) - start;
	if (start >= ft_strlen(s))
		len = 0;
	chaine = malloc(len + 1);
	if (chaine == NULL)
		return (NULL);
	while (cpt < len)
	{
		chaine[cpt] = s[start + cpt];
		cpt++;
	}
	chaine[cpt] = '\0';
	return (chaine);
}
