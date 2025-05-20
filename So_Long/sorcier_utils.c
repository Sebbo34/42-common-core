/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorcier_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 21:58:32 by sbo               #+#    #+#             */
/*   Updated: 2024/01/24 14:49:03 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	ctrl(t_maps *maps, t_sorc *sorc, char c)
{
	int	pos_x;
	int	pos_y;

	pos_x = sorc->x;
	pos_y = sorc->y;
	if (c == 'h')
		pos_y--;
	else if (c == 'b')
		pos_y++;
	else if (c == 'd')
		pos_x++;
	else if (c == 'g')
		pos_x--;
	while (maps->y != pos_y)
		maps = maps->next;
	return (maps->line[pos_x]);
}

void	new_sorc(t_data *data, t_sorc **tmp2, int x, int y)
{
	t_sorc	*tmp3;

	(*tmp2)->x = x;
	(*tmp2)->y = y;
	tmp3 = malloc(sizeof(t_sorc));
	if (!tmp3)
		end_prog(data);
	tmp3->next = NULL;
	(*tmp2)->next = tmp3;
	(*tmp2) = tmp3;
}

void	find_sorc(t_data *data)
{
	int		i;
	t_maps	*temp;
	t_sorc	*tmp2;

	temp = data->maps;
	data->sorc = malloc(sizeof(t_sorc));
	if (!data->sorc)
		ft_destroy(data, 1);
	data->sorc->next = NULL;
	tmp2 = data->sorc;
	while (temp->next)
	{
		i = 0;
		while (i < ft_strlen(temp->line))
		{
			if (temp->line[i] == 'S')
				new_sorc(data, &tmp2, i, temp->y);
			i++;
		}
		temp = temp->next;
	}
	tmp2 = NULL;
}

int	anim_sorc(t_data *data, t_sorc *tmp)
{
	clock_t	t;

	t = clock();
	if (((t * 12) / CLOCKS_PER_SEC) % 3 == 0)
		push_image(data, 'S', (tmp->x) * 32, (tmp->y) * 32 + 16);
	else if (((t * 12) / CLOCKS_PER_SEC) % 3 == 1)
		push_image(data, '2', (tmp->x) * 32, (tmp->y) * 32 + 16);
	else
		push_image(data, '3', (tmp->x) * 32, (tmp->y) * 32 + 16);
	return (0);
}
