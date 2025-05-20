/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 13:16:09 by sbo               #+#    #+#             */
/*   Updated: 2024/02/15 14:19:30 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_philo(int i, t_philo **philo, int check)
{
	int	j;

	j = 0;
	free(philo[j]->data->global);
	free(philo[j]->data);
	while (j < i)
	{
		free(philo[j]->thread);
		free(philo[j]->fork);
		free(philo[j]);
		j++;
	}
	if (check >= 3)
		free(philo[i]->fork);
	if (check >= 2)
		free(philo[i]->thread);
	if (check >= 1)
		free(philo[i]);
	free(philo);
}

t_data	*init_data(char **argv, int argc)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->life = 1;
	data->nbr_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->number_of_meal = ft_atoi(argv[5]);
	else
		data->number_of_meal = -1;
	if (data->nbr_philo < -1 || data->time_to_die < -1 || data->time_to_eat < -1
		|| data->time_to_sleep < -1 || data->number_of_meal < -1
		|| data->nbr_philo == 0)
		return (free(data), NULL);
	data->global = malloc(sizeof(pthread_mutex_t));
	if (!data->global)
		return (free(data), NULL);
	if (pthread_mutex_init(data->global, NULL) != 0)
		return (free(data->global), free(data), NULL);
	return (data);
}

void	next_philo(t_philo **philo, int nbr)
{
	int	i;

	i = 0;
	while (i < nbr - 1)
	{
		philo[i]->next = philo[i + 1];
		i++;
	}
	philo[i]->next = philo[0];
}

int	creat_philo(t_philo **philo, t_data *data, int nbr)
{
	int	i;

	i = 0;
	while (i < nbr)
	{
		philo[i] = malloc(sizeof(t_philo));
		if (!philo[i])
			return (free_philo(i, philo, 0), 0);
		philo[i]->fork_status = 1;
		philo[i]->n = i + 1;
		philo[i]->thread = malloc(sizeof(pthread_t));
		if (!philo[i]->thread)
			return (free_philo(i, philo, 1), 0);
		philo[i]->last_meal = get_time();
		philo[i]->data = data;
		philo[i]->number_of_meal = data->number_of_meal;
		philo[i]->fork = malloc(sizeof(pthread_mutex_t));
		if (!philo[i]->fork)
			return (free_philo(i, philo, 2), 0);
		if (pthread_mutex_init(philo[i]->fork, NULL) != 0)
			return (free_philo(i, philo, 3), 0);
		i++;
	}
	next_philo(philo, nbr);
	return (1);
}
