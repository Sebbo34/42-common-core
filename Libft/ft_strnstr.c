/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 17:58:29 by sbo               #+#    #+#             */
/*   Updated: 2023/11/13 17:58:35 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	temp;
	size_t	lenght;

	if (len == 0 && big == NULL)
		return (NULL);
	if (!*little)
		return ((char *)big);
	lenght = ft_strlen(little);
	i = 0;
	while (i < ft_strlen(big) && i < len)
	{
		temp = 0;
		while (big[i + temp] == little[temp] && i + temp < len)
		{
			temp++;
			if (temp == lenght)
			{
				return ((char *)&big[i]);
			}
		}
		i++;
	}
	return (NULL);
}
/*
int main(void)
{
	printf("mot = %s",ft_strnstr("01234a56789","4a",6));
}
*/