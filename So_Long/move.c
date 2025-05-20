/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:22:29 by seb               #+#    #+#             */
/*   Updated: 2024/01/23 18:02:20 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_move_perso(t_data *data, char s, char c, t_perso *perso)
{
	if (s != '1' && s != 'E')
	{
		push_image(data, '0', perso->x * 32, perso->y * 32 + 16);
		if (c == 'h')
			perso->y--;
		if (c == 'b')
			perso->y++;
		if (c == 'd')
			perso->x++;
		if (c == 'g')
			perso->x--;
		if (s == 'C')
		{
			modif_maps(data, perso->x, perso->y, '0');
			perso->item++;
		}
		push_perso(data, perso, perso->x * 32, (perso->y) * 32 + 16);
		perso->nbr_mouv++;
	}
}

void	ft_move(t_data *data, t_maps *maps, t_perso *perso, char c)
{
	char	s;

	s = ctrl_struc(maps, perso, c);
	ft_move_perso(data, s, c, perso);
	if (check_item(maps) == 1)
		open_the_door(data);
	if (s == 'E' && check_item(maps) == 1)
		end_prog(data);
}
