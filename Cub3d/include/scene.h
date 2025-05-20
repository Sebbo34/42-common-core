/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:47:56 by sbo               #+#    #+#             */
/*   Updated: 2024/04/24 13:54:46 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "map.h"
# include "assets.h"
# include "player.h"
# include <stdbool.h>

typedef struct s_scene
{
	t_assets	assets;
	t_map		map;
	t_player	player;
}	t_scene;

bool		load_scene(char *path, t_scene *scene, void *mlx_context);
void		destroy_scene(t_scene scene, void *mlx_context);
void		display_column(t_scene scene, t_image background, int index);

#endif