/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 13:23:24 by sbo               #+#    #+#             */
/*   Updated: 2024/04/22 13:14:51 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdlib.h>

bool	push_str(t_str_array *array, t_str str)
{
	t_str	*new_strs;

	new_strs = malloc((array->len + 1) * sizeof(t_str));
	if (!new_strs)
		return (false);
	ft_memcpy(new_strs, array->strs, array->len * sizeof(t_str));
	free(array->strs);
	array->strs = new_strs;
	array->strs[array->len] = str;
	array->len++;
	return (true);
}

int	get_max_len(t_str_array *lines)
{
	int	i;
	int	max_len;

	i = 0;
	max_len = 0;
	while (i < lines->len)
	{
		if ((int) lines->strs[i].len > max_len)
			max_len = lines->strs[i].len;
		i++;
	}
	return (max_len);
}

void	free_str_array(t_str_array array)
{
	int	i;

	i = 0;
	while (i < array.len)
	{
		free(array.strs[i].str);
		i++;
	}
	free(array.strs);
}
