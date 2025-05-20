/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 21:55:51 by sbo               #+#    #+#             */
/*   Updated: 2024/01/24 12:30:49 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_item(t_maps *maps)
{
	int		i;
	t_maps	*temp;

	i = 0;
	temp = maps;
	while (temp->next)
	{
		i = 0;
		while (temp->line[i])
		{
			if (temp->line[i] == 'C')
				return (0);
			i++;
		}
		temp = temp->next;
	}
	return (1);
}

void	modif_maps(t_data *data, int x, int y, char c)
{
	t_maps	*temp;

	temp = data->maps;
	while (temp->y != y)
		temp = temp->next;
	temp->line[x] = c;
}

void	find_perso(t_data *data)
{
	int		i;
	t_maps	*temp;

	temp = data->maps;
	data->perso = malloc(sizeof(t_perso));
	if (!data->perso)
		ft_destroy(data, 0);
	while (temp->next)
	{
		i = 0;
		while (i < ft_strlen(temp->line))
		{
			if (temp->line[i] == 'P')
			{
				data->perso->x = i;
				data->perso->y = temp->y;
				data->perso->nbr_mouv = 0;
				data->perso->item = 0;
			}
			i++;
		}
		temp = temp->next;
	}
}

char	ctrl_struc(t_maps *maps, t_perso *perso, char c)
{
	int	pos_x;
	int	pos_y;

	pos_x = perso->x;
	pos_y = perso->y;
	if (c == 'h')
		pos_y--;
	if (c == 'b')
		pos_y++;
	if (c == 'd')
		pos_x++;
	if (c == 'g')
		pos_x--;
	while (maps->y != pos_y)
		maps = maps->next;
	return (maps->line[pos_x]);
}

void	push_perso(t_data *data, t_perso *perso, int x, int y)
{
	if (perso->item == 0)
		push_image(data, 'P', x, y);
	else if (perso->item == 1)
		push_image(data, 'U', x, y);
	else if (perso->item == 2)
		push_image(data, 'D', x, y);
	else
		push_image(data, 'T', x, y);
}
