/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:43:41 by sbo               #+#    #+#             */
/*   Updated: 2024/04/24 13:50:25 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"
#include <math.h>

void	move_player(t_keys keys, t_player *player)
{
	float		forward_movement;
	float		side_movement;
	const float	diag_coef = sqrtf(2) / 2;

	forward_movement = keys.w - keys.s;
	side_movement = keys.d - keys.a;
	if (forward_movement)
		side_movement *= diag_coef;
	if (side_movement)
		forward_movement *= diag_coef;
	player->x += forward_movement * player->direction_x * WALKING_SPEED;
	player->y += forward_movement * player->direction_y * WALKING_SPEED;
	player->x += side_movement * -player->direction_y * WALKING_SPEED;
	player->y += side_movement * player->direction_x * WALKING_SPEED;
	turn_player(keys, player);
}

void	turn_player(t_keys keys, t_player *player)
{
	int		rotation_movement;
	float	rotation_cos;
	float	rotation_sin;
	float	old_direction_x;
	float	old_direction_y;

	rotation_movement = keys.right - keys.left;
	if (rotation_movement == 0)
		return ;
	rotation_cos = cos(TURNING_SPEED * 2 * M_PI);
	rotation_sin = sin(TURNING_SPEED * 2 * M_PI) * rotation_movement;
	old_direction_x = player->direction_x;
	old_direction_y = player->direction_y;
	player->direction_x = old_direction_x * rotation_cos
		- old_direction_y * rotation_sin;
	player->direction_y = old_direction_x * rotation_sin
		+ old_direction_y * rotation_cos;
}

t_ray	ray_from_view_column(t_player player, float ratio)
{
	t_ray	ray;
	float	norm;
	float	front;
	float	side;

	ray.start_x = player.x;
	ray.start_y = player.y;
	front = cos(FOV * M_PI / 360);
	side = sin(FOV * M_PI / 360) * (2 * ratio - 1);
	norm = sqrt(front * front + side * side);
	ray.direction_x = (front / norm) * player.direction_x
		- (side / norm) * player.direction_y;
	ray.direction_y = (front / norm) * player.direction_y
		+ (side / norm) * player.direction_x;
	return (ray);
}
