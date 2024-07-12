/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 04:19:05 by igarcia2          #+#    #+#             */
/*   Updated: 2024/07/12 14:18:57 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philo_run(t_philo *philo)
{
	//CREATE MONITORING THREAD
	//
	//
	philo->last_meal = get_time_ms();
	while ((philo->dead) == 0 && philo->meals_eaten < philo->n_times_eat)
	{
		philo_eat(philo);
		//SEM meals / monitoring
		philo->meals_eaten++;
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

int	philos_start(t_data *data)
{
	int	i;
	int	pid;

	sem_init(&(data->sem), 0, data->philo_num);
	i = -1;
	data->start_time = get_time_ms();
	while (++i < data->philo_num)
	{
		pid = fork();
		if (pid == 0)
			philo_run(data->philos[i]);
		else if (pid == -1)
			print_error("Fork error\n");
		else
			data->philos[i].pid = pid;
	}
	return (pid);
}
