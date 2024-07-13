/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 13:57:08 by igarcia2          #+#    #+#             */
/*   Updated: 2024/07/13 17:13:42 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//Check if the philosophers have taken the necessary amount of meals
void	check_if_meals_eaten(t_philo *philo)
{
	sem_wait(philo->meals_eaten_sem);
	if (philo->meals_eaten >= philo->n_times_eat)
	{
		sem_post(philo->meals_eaten_sem);
		sem_wait(philo->done_sem);
		philo->done = 1;
		sem_post(philo->done_sem);
		return ;
	}
	sem_post(philo->meals_eaten_sem);
}

//Check if any philosopher dies 
void	check_if_dead(t_philo *philo)
{
	sem_wait(philo->last_meal_sem);
	if (get_time_ms() - 1 - philo->last_meal > philo->die_time)
	{
		sem_post(philo->last_meal_sem);
		sem_wait(philo->dead_sem);
		philo->dead = 1;
		sem_post(philo->dead_sem);
		print_log("is dead", get_time_ms(), philo);	
	}
	sem_post(philo->last_meal_sem);
}

//Function that monitors the status of the philosophers
void	*monitoring(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	while (1)
	{
		check_if_dead(philo);
		if (philo->n_times_eat > -1)
			check_if_meals_eaten(philo);
		sem_wait(philo->dead_sem);
		if (philo->dead || philo->done)
		{
			sem_post(philo->dead_sem);
			break ;
		}
		sem_post(philo->dead_sem);
	}
	return (NULL);
}
