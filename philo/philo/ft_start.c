/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 11:47:23 by sbo               #+#    #+#             */
/*   Updated: 2024/02/15 14:03:33 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_start_odd(t_philo *philo, t_data *data, long time_max)
{
	if (philo->n % 3 == 2 || (data->nbr_philo == philo->n
			&& philo->n % 3 == 1))
	{
		if (data->time_to_die - time_max > data->time_to_eat)
			ft_usleep(data->time_to_eat * 1000);
		else
			ft_usleep((data->time_to_die - time_max + 1) * 1000);
	}
	else if (philo->n % 3 == 0)
	{
		if (data->time_to_die - time_max > 2 * data->time_to_eat)
			ft_usleep((2 * data->time_to_eat + 1) * 1000);
		else
			ft_usleep((data->time_to_die - time_max + 3) * 1000);
	}
}

void	ft_start_even_even(t_philo *philo, t_data *data, long time_max)
{
	if ((data->time_to_eat + (philo->last_meal + (data->time_to_eat / 2))
			- get_time()) > 0 && (data->time_to_die - time_max + 1) * 1000 > 0)
	{		
		if (data->time_to_eat + (data->time_to_eat / 2) < data->time_to_die)
			ft_usleep((data->time_to_eat + (philo->last_meal
						+ (data->time_to_eat / 2) + 2) - get_time()) * 1000);
		else
			ft_usleep((data->time_to_die - time_max + 1) * 1000);
	}
}

void	ft_start(t_philo *philo)
{
	long int	time_max;

	pthread_mutex_lock(philo->data->global);
	printf("%ld %d is thinking\n", get_time(), philo->n);
	pthread_mutex_unlock(philo->data->global);
	time_max = get_time() - philo->last_meal;
	if (philo->data->nbr_philo % 2 == 1)
		ft_start_odd(philo, philo->data, time_max);
	else
	{
		if (philo->n % 2 == 0)
			ft_start_even_even(philo, philo->data, time_max);
		else
		{
			if (((philo->last_meal + (philo->data->time_to_eat / 2))
					- get_time()) > 0)
				ft_usleep((philo->last_meal + (philo->data->time_to_eat / 2)
						- get_time()) * 1000);
		}
	}
}
