/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_img.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:32:09 by sbo               #+#    #+#             */
/*   Updated: 2024/01/24 13:33:00 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	*ft_xpm_to_image(t_data *data, char *xpm, int ind)
{
	int		i;
	int		j;
	int		k;
	void	*img;

	i = 0;
	j = 0;
	k = 0;
	img = mlx_xpm_file_to_image(data->mlx_ptr, xpm, &i, &j);
	if (img == NULL)
	{
		while (k < ind)
		{
			mlx_destroy_image (data->mlx_ptr, data->image->num[k]);
			k++;
		}
		ft_lstclear(&(data->maps));
		free(data->image);
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		exit(1);
	}
	return (img);
}

void	generate_number(t_data *data)
{
	data->image->num[0] = ft_xpm_to_image(data, "00.xpm", 0);
	data->image->num[1] = ft_xpm_to_image(data, "01.xpm", 1);
	data->image->num[2] = ft_xpm_to_image(data, "02.xpm", 2);
	data->image->num[3] = ft_xpm_to_image(data, "03.xpm", 3);
	data->image->num[4] = ft_xpm_to_image(data, "04.xpm", 4);
	data->image->num[5] = ft_xpm_to_image(data, "05.xpm", 5);
	data->image->num[6] = ft_xpm_to_image(data, "06.xpm", 6);
	data->image->num[7] = ft_xpm_to_image(data, "07.xpm", 7);
	data->image->num[8] = ft_xpm_to_image(data, "08.xpm", 8);
	data->image->num[9] = ft_xpm_to_image(data, "09.xpm", 9);
}

void	ft_putnbr_img(int n, t_data *data, int x)
{
	int	i;

	if (n >= 10)
	{
		ft_putnbr_img(n / 10, data, x - 16);
		i = mlx_put_image_to_window(data->mlx_ptr,
				data->win_ptr, data->image->num[n % 10], x, 0);
		if (i < 0)
			end_prog(data);
	}
	else
	{
		i = mlx_put_image_to_window(data->mlx_ptr,
				data->win_ptr, data->image->num[n % 10], x, 0);
		if (i < 0)
			end_prog(data);
	}
}
