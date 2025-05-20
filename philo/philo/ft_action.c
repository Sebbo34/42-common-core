/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_action.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 13:52:48 by sbo               #+#    #+#             */
/*   Updated: 2024/02/18 13:54:18 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_eat(t_philo *philo)
{
	unsigned long int	time;

	time = get_time();
	pthread_mutex_lock(philo->data->global);
	if ((philo->data->life) == 0)
	{
		pthread_mutex_unlock(philo->data->global);
		return (0);
	}
	printf("%lu %d has taken a fork\n", time, philo->n);
	printf("%ld %d is eating\n", time, philo->n);
	pthread_mutex_unlock(philo->data->global);
	philo->last_meal = time;
	if (philo->data->time_to_eat < philo->data->time_to_die
		&& philo->data->time_to_eat > 6)
		ft_usleep(((time + philo->data->time_to_eat) - get_time() - 6) * 1000);
	else if (philo->data->time_to_eat < philo->data->time_to_die
		&& philo->data->time_to_eat < 6)
		return (1);
	else
		return (ft_usleep((philo->data->time_to_die + 3) * 1000), 0);
	return (1);
}

int	ft_sleep(t_philo *philo)
{
	long int	time_max;
	long int	time;

	time = get_time();
	pthread_mutex_lock(philo->data->global);
	if ((philo->data->life) == 0)
	{
		pthread_mutex_unlock(philo->data->global);
		return (0);
	}
	printf("%ld %d is sleeping\n", get_time(), philo->n);
	pthread_mutex_unlock(philo->data->global);
	time_max = get_time() - philo->last_meal;
	if ((philo->number_of_meal == 0 && philo->n % 2 == 0
			&& philo->data->nbr_philo % 2 == 0) || time_max < 0)
		return (1);
	else if ((philo->number_of_meal == 0 && philo->n % 3 == 0
			&& philo->data->nbr_philo % 2 == 1))
		return (1);
	if (time_max + philo->data->time_to_sleep < philo->data->time_to_die)
		ft_usleep(((time + philo->data->time_to_sleep) - get_time()) * 1000);
	else
		return (ft_usleep((philo->data->time_to_die - time_max + 1) * 1000), 0);
	return (1);
}

void	ft_died(t_philo *philo)
{
	pthread_mutex_lock(philo->data->global);
	if (philo->number_of_meal != 0 && philo->data->life == 1)
	{
		philo->data->life = 0;
		printf("%ld %d died\n", get_time(), philo->n);
		pthread_mutex_unlock(philo->data->global);
	}
	else
		pthread_mutex_unlock(philo->data->global);
}
