/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_from_strs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:31:08 by sbo               #+#    #+#             */
/*   Updated: 2024/04/24 13:33:58 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "player.h"
#include <stdlib.h>
#include <stdio.h>

bool	read_map_lines(int fd, t_str_array *lines)
{
	enum e_read_status	status;
	t_str				line;

	*lines = (t_str_array){NULL, 0};
	if (!get_nonempty_line(fd, &line))
		return (false);
	status = READ_OK;
	while (status != READ_END)
	{
		if (!push_str(lines, line))
			return (free(line.str), free_str_array(*lines), false);
		status = get_next_line(fd, &line);
		if (status == READ_ERROR)
			return (free(line.str), free_str_array(*lines), false);
	}
	return (true);
}

bool	char_to_player(t_player *player, float x, float y, char c)
{
	if (c == 'N')
		return (*player = (t_player){x, y, 0, -1}, true);
	else if (c == 'S')
		return (*player = (t_player){x, y, 0, 1}, true);
	else if (c == 'W')
		return (*player = (t_player){x, y, -1, 0}, true);
	else if (c == 'E')
		return (*player = (t_player){x, y, 1, 0}, true);
	return (false);
}

bool	search_player(t_str_array lines, t_player *player)
{
	int		i;
	int		j;
	bool	player_found;

	i = 0;
	player_found = false;
	while (i < lines.len)
	{
		j = 0;
		while (j < lines.strs[i].len)
		{
			if (char_to_player(player, j + 0.5, i + 0.5, lines.strs[i].str[j]))
			{
				if (player_found)
					return (printf("Error\nLine %d, Column %d: "
							"Multiple players found\n", i + 1, j + 1), false);
				player_found = true;
			}
			j++;
		}
		i++;
	}
	if (!player_found)
		printf("Error\nNo player found\n");
	return (player_found);
}

bool	char_to_tile(char c, t_tile *tile)
{
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (*tile = TILE_FLOOR, true);
	if (c == '1')
		return (*tile = TILE_WALL, true);
	if (c == ' ')
		return (*tile = TILE_VOID, true);
	return (false);
}

bool	parse_tiles(t_map map, t_str_array lines)
{
	int	i;
	int	j;

	i = 0;
	while (i < map.height)
	{
		j = 0;
		while (j < (int) lines.strs[i].len)
		{
			if (!char_to_tile(lines.strs[i].str[j],
					&map.tiles[i * map.width + j]))
				return (printf("Error\nLine %d, Column %d: "
						"Invalid character in map\n", i + 1, j + 1), false);
			j++;
		}
		while (j < map.width)
		{
			map.tiles[i * map.width + j] = TILE_VOID;
			j++;
		}
		i++;
	}
	return (true);
}
