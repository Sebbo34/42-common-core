/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_think.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:37:17 by sbo               #+#    #+#             */
/*   Updated: 2024/02/18 14:33:02 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_think_odd_philo(t_philo *philo, t_data *data)
{
	long int	time_max;

	time_max = get_time() - philo->last_meal;
	if (data->time_to_eat >= data->time_to_sleep)
	{
		if (time_max + 2 * data->time_to_eat - data->time_to_sleep
			< data->time_to_die)
			ft_usleep((2 * data->time_to_eat - data->time_to_sleep + 5) * 1000);
		else
			ft_usleep((data->time_to_die - time_max + 1) * 1000);
	}
	else
	{
		if (time_max + (data->time_to_sleep - data->time_to_eat)
			< data->time_to_die)
			ft_usleep((data->time_to_sleep - data->time_to_eat + 5) * 1000);
		else
			ft_usleep((data->time_to_die - time_max + 1) * 1000);
	}
}

int	ft_think(t_philo *philo)
{
	pthread_mutex_lock(philo->data->global);
	if ((philo->data->life) == 0)
	{
		pthread_mutex_unlock(philo->data->global);
		return (0);
	}
	printf("%ld %d is thinking\n", get_time(), philo->n);
	pthread_mutex_unlock(philo->data->global);
	if (philo->data->nbr_philo % 2 == 0)
	{
		if (philo->data->time_to_die <= 2 * philo->data->time_to_eat)
			return (ft_usleep((philo->data->time_to_die
						-(get_time() - philo->last_meal) + 3) * 1000), 0);
		if ((get_time() - philo->last_meal) + 6 < philo->data->time_to_die)
			ft_usleep((philo->data->time_to_die
					- (get_time() - philo->last_meal) - 5) * 1000);
		else if (2 * philo->data->time_to_eat
			+ philo->last_meal - get_time() >= 0)
			ft_usleep((2 * philo->data->time_to_eat
					+ philo->last_meal - get_time() + 4) * 1000);
	}
	else
		ft_think_odd_philo(philo, philo->data);
	return (1);
}
