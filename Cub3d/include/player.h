/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:55:32 by sbo               #+#    #+#             */
/*   Updated: 2024/04/25 11:38:29 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "user_input.h"
# include "map.h"
# define FOV 90

//						In turns/frame
# define TURNING_SPEED	0.005f
# define WALKING_SPEED	0.03f

typedef struct s_player
{
	float	x;
	float	y;
	float	direction_x;
	float	direction_y;
}	t_player;

void	move_player(t_keys keys, t_player *player);
void	turn_player(t_keys keys, t_player *player);
t_ray	ray_from_view_column(t_player player, float ratio);

#endif