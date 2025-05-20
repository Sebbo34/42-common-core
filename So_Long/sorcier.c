/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorcier.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 21:13:53 by sbo               #+#    #+#             */
/*   Updated: 2024/01/24 14:43:58 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	attrib_dir(int random)
{
	char	c;

	if (random == 0)
		c = 'd';
	if (random == 1)
		c = 'g';
	if (random == 2)
		c = 'b';
	if (random == 3)
		c = 'h';
	return (c);
}

void	pas_sorc(t_data *data, t_sorc *tmp, int random)
{
	char	c;

	c = attrib_dir(random);
	if (ctrl(data->maps, tmp, c) != '1' && ctrl(data->maps, tmp, c) != 'E')
	{
		if (ctrl(data->maps, tmp, '5') == 'C')
			push_image(data, 'C', (tmp->x) * 32, (tmp->y) * 32 + 16);
		else
			push_image(data, '0', (tmp->x) * 32, (tmp->y) * 32 + 16);
		if (random == 0)
			tmp->x++;
		if (random == 1)
			tmp->x--;
		if (random == 2)
			tmp->y++;
		if (random == 3)
			tmp->y--;
		push_image(data, 'S', (tmp->x) * 32, (tmp->y) * 32 + 16);
	}
}

int	move_sorc(t_data *data)
{
	int		random;
	clock_t	t;
	t_sorc	*tmp;

	t = clock();
	tmp = data->sorc;
	if ((t - data->start) > CLOCKS_PER_SEC / 3)
	{
		while (tmp -> next)
		{
			random = rand() % 4;
			pas_sorc(data, tmp, random);
			anim_sorc(data, tmp);
			tmp = tmp->next;
			data->start = t;
		}
	}
	tmp = data->sorc;
	while (tmp -> next)
	{
		if (data->perso->x == tmp->x && data->perso->y == tmp->y)
			end_prog(data);
		tmp = tmp->next;
	}
	return (0);
}
