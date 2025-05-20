/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:51:18 by sbo               #+#    #+#             */
/*   Updated: 2024/04/24 13:58:02 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "image.h"
# include "assets.h"
# include "parsing.h"
# include <stdint.h>

# define TILE_SIZE		100

enum e_hit_type
{
	HIT_NS,
	HIT_WE,
	HIT_NONE,
	HIT_IN_WALL,
};

typedef struct s_ray
{
	float	start_x;
	float	start_y;
	float	direction_x;
	float	direction_y;
}	t_ray;

typedef struct s_ray_progress
{
	float	vert_dist;
	float	hor_dist;
	float	max_dist;
}	t_ray_progress;

typedef enum e_tile_kind
{
	TILE_VOID,
	TILE_FLOOR,
	TILE_WALL,
}	t_tile;

typedef struct s_map
{
	int			width;
	int			height;
	t_tile		*tiles;
}	t_map;

typedef struct s_player	t_player;

bool			read_map_lines(int fd, t_str_array *lines);
bool			search_player(t_str_array lines, t_player *player);
bool			parse_tiles(t_map map, t_str_array lines);

bool			parse_map(int fd, t_map *map, t_player *player);

// ray_hit_rect_inside.c
float			ray_hit_rect_inside(t_ray ray, int width, int height);
float			ray_hit_vertical_lines(t_ray ray, int width);
float			ray_hit_horizontal_lines(t_ray ray, int height);

// ray_hit_rect_outside.c
enum e_hit_type	ray_hit_rect_outside(t_ray ray, int width, int height,
					float *dist);

// ray.c
void			project_ray(t_ray ray, float dist, float *out_x, float *out_y);
t_ray			offset_ray(t_ray ray, float offset_x, float offset_y);
enum e_hit_type	ray_hit_map(t_ray ray, t_map map, float *hit_dist);

// ray_hit_walls.c
enum e_hit_type	ray_hit_walls(t_ray ray, t_map map, float *hit_dist);

#endif