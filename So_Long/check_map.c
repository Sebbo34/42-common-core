/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 17:10:21 by seb               #+#    #+#             */
/*   Updated: 2024/01/24 13:52:34 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "get_next_line.h"

int	check_rect(t_maps *maps)
{
	t_maps	*temp;
	int		len;

	temp = maps;
	len = ft_strlen(temp->line);
	while (temp->next)
	{
		if (len != ft_strlen(temp->line))
			return (0);
		temp = temp->next;
	}
	return (1);
}

int	check_char(t_maps *maps, int *verif)
{
	int		i;
	t_maps	*temp;

	temp = maps;
	while (temp)
	{
		i = -1;
		while (i++ < ft_strlen(temp->line) - 1)
		{
			if (temp->line[i] != '0' && temp->line[i] != '1'
				&& temp->line[i] != 'C' && temp->line[i] != 'P'
				&& temp->line[i] != 'E' && temp->line[i] != 'S')
				return (0);
			if (temp->line[i] == 'P')
				verif[0]++;
			if (temp->line[i] == 'E')
				verif[1]++;
			if (temp->line[i] == 'C')
				verif[2] = 1;
		}
		temp = temp->next;
	}
	if (verif[0] != 1 || verif[1] != 1 || verif[2] != 1)
		return (0);
	return (1);
}

int	checkwall(t_maps *maps)
{
	t_maps	*temp;
	int		i;

	temp = maps;
	i = -1;
	while (i++ < ft_strlen(temp->line) - 1)
	{
		if (temp ->line[i] != '1')
			return (0);
	}
	temp = temp->next;
	while (temp->next->next)
	{
		if (temp->line[0] != '1'
			|| temp->line[ft_strlen(temp->line) - 1] != '1')
			return (0);
		temp = temp->next;
	}
	i = -1;
	while (i++ < ft_strlen(temp->line) - 1)
	{
		if (temp->line[i] != '1')
			return (0);
	}
	return (1);
}

int	check_all(t_maps *maps)
{
	int	tab[3];

	tab[0] = 0;
	tab[1] = 0;
	tab[2] = 0;
	if (check_char(maps, tab) == 0)
		return (3);
	if (checkwall(maps) == 0)
		return (4);
	if (checkpath(maps) == 0)
		return (5);
	if (check_rect(maps) == 0)
		return (2);
	return (0);
}
