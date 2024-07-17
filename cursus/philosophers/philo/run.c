/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:08:04 by igarcia2          #+#    #+#             */
/*   Updated: 2024/07/16 16:32:31 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//Manages the threads that represent the philosophers, who manage their actions
void	*philo_run(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	pthread_mutex_lock(philo->start_lock);
	pthread_mutex_unlock(philo->start_lock);
	if (philo->id % 2 == 0)
		usleep(50000);
	pthread_mutex_lock(philo->dead_lock);
	pthread_mutex_lock(&(philo->meal_lock));
	philo->last_meal = get_time_ms();
	pthread_mutex_unlock(&(philo->meal_lock));
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
		usleep(200);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return (NULL);
}

//Initializes the necessary mutex
void	init_mutexs(t_data *data)
{
	pthread_mutex_init(&(data->write_lock), NULL);
	pthread_mutex_init(&(data->dead_lock), NULL);
	pthread_mutex_init(&(data->start_lock), NULL);
	pthread_mutex_lock(&(data->start_lock));
}

//Initialize threads for each philosopher
void	philos_start(t_data *data)
{
	int	i;

	init_mutexs(data);
	i = -1;
	while (++i < data->philo_num)
		pthread_create(&(data->philos[i].thread), NULL, philo_run,
			(void *)&(data->philos[i]));
	pthread_mutex_unlock(&(data->start_lock));
	data->start_time = get_time_ms();
	monitoring(data);
}
