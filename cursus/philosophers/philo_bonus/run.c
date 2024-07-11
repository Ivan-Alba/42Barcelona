/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 04:19:05 by igarcia2          #+#    #+#             */
/*   Updated: 2024/07/11 15:55:00 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_run(t_philo *philo)
{
	philo->last_meal = get_time_ms();
	while ((philo->dead) == 0)
	{
		philo_eat(philo);
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
	}
	return (pid);
}
