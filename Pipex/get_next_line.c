/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:49:19 by sbo               #+#    #+#             */
/*   Updated: 2024/01/26 19:12:07 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strchr(const char *s, int c, int j)

{
	int	cpt;

	if (s == NULL)
		return (-1);
	cpt = 0;
	c = (unsigned char)c;
	while (cpt < j && s[cpt])
	{
		if (s[cpt] == c)
		{
			return (cpt);
		}
		cpt++;
	}
	return (-1);
}

void	ft_cpy(char *dst, char *src, int *tab, int *index)
{
	int	cpt;

	if (src == NULL)
		return ;
	cpt = 0;
	tab[1]++;
	while (tab[1] + cpt < tab[0] && tab[1] != 0)
	{
		dst[cpt] = src[tab[1] + cpt];
		cpt++;
	}
	*index = cpt;
	dst[cpt] = 0;
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	static int	index = 0;
	char		*chaine;
	int			tab[2];

	tab[0] = 0;
	tab[1] = BUFFER_SIZE;
	chaine = NULL;
	if (index != 0)
	{
		chaine = ft_strdup(buffer, index, tab);
		if (chaine == NULL)
			return (NULL);
	}
	while (check_line(chaine, tab[0], tab[1]) == 0 && tab[1] == BUFFER_SIZE)
	{
		tab[1] = read(fd, buffer, BUFFER_SIZE);
		if (tab[1] < 0)
			return (NULL);
		chaine = join_gnl(chaine, buffer, tab[1], &tab[0]);
		if (chaine == NULL)
			return (NULL);
	}
	tab[1] = ft_strchr(chaine, '\n', tab[0]);
	return (ft_cpy(buffer, chaine, tab, &index), ft_strdup_f(chaine, tab[1]));
}

/*  #include <stdio.h>
  int main (void)

{
	int fd;
	char *chaine;

	fd = open ("test.txt", -O_RDONLY);
	chaine = get_next_line(1);
	printf ("%s",chaine);
	free(chaine);


	//chaine = get_next_line(fd);
	//printf ("%s",chaine);free(chaine);
} */