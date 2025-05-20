/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:04:44 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/02/12 12:49:32 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/printf.h"
#include <stdlib.h>

static int	count_word(char *s, char c)
{
	int	word;

	word = 0;
	while (s && *s)
	{
		while (*s && (*s == c))
			s++;
		if (*s && !(*s == c))
		{
			word++;
			while (*s && !(*s == c))
				s++;
		}
	}
	return (word);
}

static int	ft_strlen_c(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && !(s[i] == c) && s[i] != '\0')
		i++;
	return (i);
}

static char	*malloc_word(char *s, char c)
{
	char	*word;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen_c(s, c);
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	while (s[i] && !(s[i] == c))
	{
		word[i] = s[i];
		i++;
	}
	word[i] = 0;
	return (word);
}

char	**ft_split(char *str, char c)
{
	char	**tab;
	char	*s;
	int		i;

	s = str;
	if (!s)
		return (NULL);
	tab = (char **)malloc(sizeof(char *) * (count_word(s, c) + 1));
	if (!tab)
		return (NULL);
	i = 0;
	while (s && *s)
	{
		while (*s && (*s == c))
			s++;
		if (*s && !(*s == c))
		{
			tab[i] = malloc_word(s, c);
			i++;
			while (*s && !(*s == c))
				s++;
		}
	}
	tab[i] = NULL;
	return (tab);
}
