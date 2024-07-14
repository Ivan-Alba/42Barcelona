/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 04:19:05 by igarcia2          #+#    #+#             */
/*   Updated: 2024/07/14 15:32:30 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//Controls the loop of philosophers' actions
void	philo_action_loop(t_philo *philo)
{
	sem_wait(philo->dead_sem);
	sem_wait(philo->done_sem);
	while ((philo->dead) == 0 && philo->done == 0)
	{
		sem_post(philo->done_sem);
		sem_post(philo->dead_sem);
		philo_eat(philo);
		sem_wait(philo->meals_eaten_sem);
		philo->meals_eaten++;
		sem_post(philo->meals_eaten_sem);
		philo_sleep(philo);
		philo_think(philo);
		sem_wait(philo->dead_sem);
		sem_wait(philo->done_sem);
	}
	sem_post(philo->dead_sem);
	sem_post(philo->done_sem);
}

//Manages the creation of threads for processes and process actions
int	philo_run(t_philo *philo, t_data *data)
{
	sem_wait(data->start_sem);
	sem_post(data->start_sem);
	pthread_create(&(philo->thread), NULL, monitoring, (void *)(philo));
	if (philo->id % 2)
		usleep(50000);
	sem_wait(philo->last_meal_sem);
	philo->last_meal = get_time_ms();
	sem_post(philo->last_meal_sem);
	philo_action_loop(philo);
	pthread_join(philo->thread, NULL);
	if (philo->dead)
		exit(philo->id);
	exit(0);
}

//Function that handles the creation of philosopher's processes
int	philos_start(t_data *data)
{
	int	i;
	int	pid;

	i = -1;
	sem_wait(data->start_sem);
	data->start_time = get_time_ms();
	while (++i < data->philo_num)
	{
		pid = fork();
		if (pid == 0)
			philo_run(&(data->philos[i]), data);
		else if (pid == -1)
		{
			while (--i >= 0)
				kill(data->philos[i].pid, SIGKILL);
			return (1);
		}
		else
			data->philos[i].pid = pid;
	}
	sem_post(data->start_sem);
	return (0);
}
