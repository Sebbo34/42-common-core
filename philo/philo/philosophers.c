/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 12:55:19 by sbo               #+#    #+#             */
/*   Updated: 2024/02/15 16:10:33 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_action(t_philo *philo)
{
	long int	time;

	philo->fork_status = 0;
	time = get_time() + philo->data->time_to_eat;
	if (ft_eat(philo) == 0)
	{
		pthread_mutex_unlock(philo->fork);
		return (0);
	}
	philo->fork_status = 1;
	pthread_mutex_unlock(philo->fork);
	pthread_mutex_lock(philo->next->fork);
	philo->next->fork_status = 1;
	pthread_mutex_unlock(philo->next->fork);
	while (get_time() < time)
		usleep(1);
	philo->number_of_meal--;
	if (ft_sleep(philo) == 0)
		return (0);
	if (ft_think(philo) == 0)
		return (0);
	return (1);
}

void	ft_unlock(t_philo *philo)
{
	pthread_mutex_unlock(philo->fork);
	pthread_mutex_lock(philo->next->fork);
	philo->next->fork_status = 1;
	pthread_mutex_unlock(philo->next->fork);
}

void	*job(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *) arg;
	ft_start(philo);
	while (is_alive(philo) && philo->number_of_meal != 0)
	{
		pthread_mutex_lock(philo->next->fork);
		if (philo->next->fork_status == 1)
		{
			philo->next->fork_status = 0;
			pthread_mutex_unlock(philo->next->fork);
			pthread_mutex_lock(philo->fork);
			if (philo->fork_status == 1)
			{
				if (ft_action(philo) == 0)
					break ;
			}	
			else
				ft_unlock(philo);
		}
		else
			pthread_mutex_unlock(philo->next->fork);
	}
	ft_died(philo);
	return (NULL);
}

int	ft_create_thread(t_philo **philo, int nbr_philo)
{
	int	i;

	i = 0;
	while (i < nbr_philo)
	{
		if (pthread_create(philo[i]->thread, NULL, job, philo[i]) != 0)
			return (0);
		i++;
	}
	i = 0;
	while (i < nbr_philo)
	{
		pthread_join(*(philo[i]->thread), NULL);
		i++;
	}
	free_philo(nbr_philo - 1, philo, 4);
	return (1);
}

int	main(int argc, char **argv)
{
	t_philo	**philo;
	t_data	*data;
	int		i;

	i = 0;
	if (argc < 5 || argc > 6)
	{
		printf("Invalid number of args\n");
		return (0);
	}
	data = init_data(argv, argc);
	if (!data)
	{
		printf ("Error\n");
		return (0);
	}
	philo = malloc(data->nbr_philo * sizeof(t_philo *));
	if (!philo)
		return (0);
	if (creat_philo(philo, data, data->nbr_philo) == 0)
		return (0);
	if (ft_create_thread(philo, data->nbr_philo) == 0)
		printf("Error dans la creation du thread\n");
}
