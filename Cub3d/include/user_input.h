/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_input.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:44:56 by sbo               #+#    #+#             */
/*   Updated: 2024/04/22 12:19:48 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_INPUT_H
# define USER_INPUT_H

# include <stdbool.h>

typedef struct s_keys
{
	bool	a;
	bool	d;
	bool	w;
	bool	s;
	bool	left;
	bool	right;
}	t_keys;

typedef struct s_key_event_context
{
	t_keys	*keys;
	void	*mlx_context;
}	t_key_event_context;

int		key_press(int keycode, t_key_event_context *context);
int		key_release(int keycode, t_key_event_context *context);

#endif