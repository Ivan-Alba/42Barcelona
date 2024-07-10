/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 04:19:05 by igarcia2          #+#    #+#             */
/*   Updated: 2024/07/10 15:57:47 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philo_run(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	pthread_mutex_lock(philo->start_lock);
	pthread_mutex_unlock(philo->start_lock);
	if (philo->id % 2 == 0)
		usleep(50000);
	pthread_mutex_lock(philo->dead_lock);
	while (*(philo->dead) == 0)
	{
		pthread_mutex_unlock(philo->dead_lock);
		philo_eat(philo);
		pthread_mutex_lock(&(philo->meals_eaten_lock));
		philo->meals_eaten++;
		pthread_mutex_unlock(&(philo->meals_eaten_lock));
		philo_sleep(philo);
		philo_think(philo);
		pthread_mutex_lock(philo->dead_lock);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return (NULL);
}

void	init_mutexs(t_data *data)
{
	pthread_mutex_init(&(data->write_lock), NULL);
	pthread_mutex_init(&(data->start_lock), NULL);
	pthread_mutex_init(&(data->dead_lock), NULL);
	pthread_mutex_lock(&(data->start_lock));
}

void	philos_start(t_data *data)
{
	int	i;

	init_mutexs(data);
	i = -1;
	while (++i < data->philo_num)
		pthread_create(&(data->philos[i].thread), NULL, philo_run,
			(void *)&(data->philos[i]));
	data->start_time = get_time_ms();
	pthread_mutex_unlock(&(data->start_lock));
	monitoring(data);
}
