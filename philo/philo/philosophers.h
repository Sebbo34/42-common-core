/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 21:11:52 by sbo               #+#    #+#             */
/*   Updated: 2024/02/18 14:40:01 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/types.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/time.h>

typedef struct s_data
{
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					life;
	int					nbr_philo;
	int					number_of_meal;
	pthread_mutex_t		*global;
}	t_data;

typedef struct s_philo
{
	int					n;
	long int			last_meal;
	int					number_of_meal;
	int					fork_status;
	struct s_philo		*next;
	pthread_mutex_t		*fork;
	pthread_t			*thread;
	t_data				*data;
}	t_philo;

int					ft_atoi(char *nptr);
long int			get_time(void);
int					is_alive(t_philo *philo);
int					ft_eat(t_philo *philo);
int					ft_think(t_philo *philo);
int					ft_sleep(t_philo *philo);
void				ft_start(t_philo *philo);
t_data				*init_data(char **argv, int argc);
void				free_philo(int i, t_philo **philo, int check);
int					creat_philo(t_philo **philo, t_data *data, int nbr);
void				ft_died(t_philo *philo);
void				ft_usleep(long long int time);

#endif
