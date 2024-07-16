/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:09:08 by igarcia2          #+#    #+#             */
/*   Updated: 2024/07/16 12:30:09 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//Controls the loop of philosophers' actions
void	philo_action_loop(t_philo *philo)
{
	while (1)
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
		usleep(200);
	}
}

//Manages the creation of threads for processes and process actions
void	philo_run(t_philo *philo, t_data *data)
{
	sem_wait(data->start_sem);
	sem_post(data->start_sem);
	if (pthread_create(&(philo->thread), NULL, monitoring,
			(void *)(philo)) == -1)
	{
		print_error("Error creating threads\n", data);
		exit(1);
	}
	if (philo->id % 2)
		usleep(20000);
	sem_wait(philo->last_meal_sem);
	philo->last_meal = get_time_ms();
	sem_post(philo->last_meal_sem);
	philo_action_loop(philo);
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
