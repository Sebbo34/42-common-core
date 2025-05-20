/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_struc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 21:54:21 by sbo               #+#    #+#             */
/*   Updated: 2024/01/23 16:15:39 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "get_next_line.h"

char	*ft_cpyline(char	*src)
{
	char	*cpy;
	int		cpt;

	cpy = (char *)malloc(ft_strlen(src) + 1);
	if (cpy == NULL)
		return (NULL);
	cpt = 0;
	while (src[cpt] != '\0' && src[cpt] != '\n')
	{
		cpy[cpt] = src [cpt];
		cpt++;
	}
	cpy[cpt] = '\0';
	return (cpy);
}

t_maps	*creat_struc(int fd)
{
	t_maps	*maps;
	t_maps	*first;
	char	*line;
	int		y;

	y = 0;
	line = get_next_line(fd);
	if (!line)
		return (NULL);
	maps = ft_lstnew(line, &y);
	if (!maps)
		return (NULL);
	first = maps;
	while (line)
	{
		line = get_next_line(fd);
		if (ft_strcmp(strerror(errno), "Success") != 0)
			return (ft_lstclear(&first), NULL);
		maps = ft_lstnew(line, &y);
		if (ft_strcmp(strerror(errno), "Success") != 0)
			return (ft_lstclear(&first), NULL);
		ft_lstadd_back(&first, maps);
	}
	return (first);
}

t_maps	*cpy_struc(t_maps *src)
{
	t_maps	*maps;
	t_maps	*first;
	t_maps	*tmp;
	char	*line;
	int		y;

	y = 0;
	tmp = src;
	while (tmp->next)
	{
		line = ft_cpyline(tmp->line);
		if (ft_strcmp(strerror(errno), "Success") != 0)
			return (NULL);
		maps = ft_lstnew(line, &y);
		if (ft_strcmp(strerror(errno), "Success") != 0)
			return (NULL);
		if (y == 1)
			first = maps;
		else
			ft_lstadd_back(&first, maps);
		tmp = tmp->next;
	}
	return (first);
}
