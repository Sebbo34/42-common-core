/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 14:52:30 by sbo               #+#    #+#             */
/*   Updated: 2024/02/14 16:14:16 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long int	get_time(void)
{
	struct timeval	tv;
	long int		time;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000;
	time = time + (tv.tv_usec / 1000);
	return (time);
}

int	is_alive(t_philo *philo)
{
	if (get_time() - philo->last_meal > philo->data->time_to_die)
		return (0);
	else
		return (1);
}

void	ft_usleep(long long int time)
{
	long long int	t;

	t = get_time();
	while (((t + (time / 1000)) - get_time()) * 1000 > 50000)
	{
		usleep(50000);
	}
	usleep(((t + (time / 1000)) - get_time()) * 1000);
}
