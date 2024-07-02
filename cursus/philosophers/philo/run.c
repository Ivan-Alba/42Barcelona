/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 04:19:05 by igarcia2          #+#    #+#             */
/*   Updated: 2024/07/02 04:19:08 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philo_run(void *param)
{
	//BLOQUEO HASTA QUE TODOS LOS HILOS ESTAN CREADOS
	t_philo *philo;
	philo = (t_philo *)param;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (*(philo->dead) == 0)
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}


void	check_if_dead(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		pthread_mutex_lock(&(data->philos[i].meal_lock));
		if (get_time_in_milliseconds() - data->philos[i].last_meal >= data->philos[i].time_to_die)
		{
			pthread_mutex_unlock(&(data->philos[i].meal_lock));
			pthread_mutex_lock(&(data->dead_lock));
			data->dead_flag = 1;
			pthread_mutex_unlock(&(data->dead_lock));
			print_log("is dead", get_time_in_milliseconds(), &(data->philos[i]));
			break;
		}
		pthread_mutex_unlock(&(data->philos[i].meal_lock));
		i++;
	}
}

void	init_mutexs(t_data *data)
{
	pthread_mutex_init(&(data->write_lock), NULL);
	//pthread_mutex_init(&(data->meal_lock), NULL);
	pthread_mutex_init(&(data->dead_lock), NULL);
}

void	philos_start(t_data *data)
{
	int i;

	init_mutexs(data);
	data->start_time = get_time_in_milliseconds();
	i = 0;
	while (i < data->philo_num)
	{
		pthread_create(&(data->philos[i].thread), NULL, philo_run, (void *)&(data->philos[i]));
		i++;
	}

	while (1)
	{
		check_if_dead(data);
		pthread_mutex_lock(&(data->dead_lock));
		if (data->dead_flag == 1)
		{
			pthread_mutex_unlock(&(data->dead_lock));
			break;
		}
		pthread_mutex_unlock(&(data->dead_lock));
	}
	//JOIN HILOS
	i = 0;
	while (i < data->philo_num)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}
