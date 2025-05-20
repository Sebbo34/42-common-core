/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkpath.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 21:52:44 by sbo               #+#    #+#             */
/*   Updated: 2024/01/24 12:29:55 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "get_next_line.h"

void	initcoor(t_maps *maps, t_sorc *coor)
{
	t_maps	*tmp;
	int		i;

	tmp = maps;
	while (tmp->next)
	{
		i = 0;
		while (tmp->line[i])
		{
			if (tmp->line[i] == 'P')
			{
				coor->x = i;
				coor->y = tmp->y;
				coor->next = NULL;
				return ;
			}
			i++;
		}
		tmp = tmp->next;
	}
}

void	modif_maps2(t_maps *maps, int x, int y, char c)
{
	t_maps	*temp;

	temp = maps;
	while (temp->y != y)
		temp = temp->next;
	temp->line[x] = c;
}

void	findpathrec(t_maps *maps, t_sorc *coor)
{
	modif_maps2(maps, coor->x, coor->y, 'P');
	find_path(maps, coor);
}

void	find_path(t_maps *maps, t_sorc *coor)
{
	if (ctrl(maps, coor, 'h') == '0' || ctrl(maps, coor, 'h') == 'C')
	{
		coor->y--;
		findpathrec(maps, coor);
		coor->y++;
	}
	if (ctrl(maps, coor, 'b') == '0' || ctrl(maps, coor, 'b') == 'C')
	{
		coor->y++;
		findpathrec(maps, coor);
		coor->y--;
	}
	if (ctrl(maps, coor, 'g') == '0' || ctrl(maps, coor, 'g') == 'C')
	{
		coor->x--;
		findpathrec(maps, coor);
		coor->x++;
	}
	if (ctrl(maps, coor, 'd') == '0' || ctrl(maps, coor, 'd') == 'C')
	{
		coor->x++;
		findpathrec(maps, coor);
		coor->x--;
	}
}

int	checkpath(t_maps *maps)
{
	t_sorc	*coor;
	t_maps	*cpy;

	coor = malloc(sizeof(t_sorc));
	if (!coor)
		(ft_lstclear(&maps), exit(1));
	cpy = cpy_struc(maps);
	if (!cpy)
		(ft_lstclear(&maps), free(coor), exit(1));
	initcoor(cpy, coor);
	find_path(cpy, coor);
	if (check_item(cpy) == 0)
	{
		ft_lstclear(&cpy);
		free(coor);
		return (0);
	}
	else
	{
		free(coor);
		ft_lstclear(&cpy);
		return (1);
	}
}
