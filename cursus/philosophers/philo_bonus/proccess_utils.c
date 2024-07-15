/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proccess_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 13:56:37 by igarcia2          #+#    #+#             */
/*   Updated: 2024/07/15 14:29:17 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//Deletes the semaphore files before and after each program execution
void	unlink_sem(void)
{
	sem_unlink("/last_meal_sem");
	sem_unlink("/meals_eaten_sem");
	sem_unlink("/forks_sem");
	sem_unlink("/write_sem");
	sem_unlink("/start_sem");
}

//Kills all processes in case of a philosopher death or error
void	kill_all_proccesses(t_data *data, int error_code)
{
	int	i;

	i = -1;
	while (++i < data->philo_num)
	{
		if (i + 1 != error_code)
			kill(data->philos[i].pid, SIGKILL);
	}
}

//Displays details on the exit status of a terminated process
void	status_info(int status)
{
	int	exit_status;
	int	term_signal;

	if (WIFEXITED(status))
	{
		exit_status = WEXITSTATUS(status);
		printf("El proceso hijo terminó normalmente.\n");
		printf("Estado de salida del hijo: %d\n", exit_status);
	}
	else if (WIFSIGNALED(status))
	{
		term_signal = WTERMSIG(status);
		printf("El proceso hijo terminó debido a una señal.\n");
		printf("Señal que terminó el hijo: %d\n", term_signal);
	}
	else
	{
		printf("El proceso hijo terminó de manera anormal.\n");
	}
}

//Initializes the required semaphores for each philosopher
void	init_philos_sem(t_philo *philo)
{
	philo->last_meal_sem = sem_open("/last_meal_sem", O_CREAT, 0644, 1);
	philo->meals_eaten_sem = sem_open("/meals_eaten_sem", O_CREAT, 0644, 1);
}
