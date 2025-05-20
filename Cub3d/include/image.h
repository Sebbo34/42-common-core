/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:59:15 by sbo               #+#    #+#             */
/*   Updated: 2024/04/23 18:53:56 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_H
# define IMAGE_H

# include <stdint.h>
# include <stdbool.h>

typedef union u_color
{
	struct {
		uint8_t	b;
		uint8_t	g;
		uint8_t	r;
	};
	int	hex;
}	t_color;

typedef struct s_image
{
	void	*mlx_image;
	int		width;
	int		height;
	t_color	*pixels;
}	t_image;

typedef struct s_rect
{
	int32_t	start_x;
	int32_t	start_y;
	int		width;
	int		height;
}	t_rect;

typedef struct s_image_column
{
	t_image	image;
	int		index;
}	t_image_column;

void	put_pixel(t_image image, int x, int y, t_color color);
t_color	get_pixel(t_image image, int x, int y);

bool	create_image(void *mlx_context, t_image *image, int width,
			int height);
bool	load_image(void *mlx_context, t_image *image, char *path);
void	destroy_image(void *mlx_context, t_image image);

t_rect	clamp_rect(t_rect rect, int width, int height);
void	fill_rect(t_rect rect, t_image image, t_color color);

bool	parse_intensity(uint8_t *intensity, char **line);
bool	parse_color(t_color *color, char *line);

#endif