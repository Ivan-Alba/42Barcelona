/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:08:50 by igarcia2          #+#    #+#             */
/*   Updated: 2024/07/16 12:08:52 by igarcia2         ###   ########.fr       */
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
		exit(0);
		return ;
	}
	sem_post(philo->meals_eaten_sem);
}

//Check if any philosopher dies 
void	check_if_dead(t_philo *philo)
{
	sem_wait(philo->last_meal_sem);
	if (get_time_ms() - philo->last_meal > philo->die_time)
	{
		sem_post(philo->last_meal_sem);
		print_log("is dead", get_time_ms(), philo);
		exit(philo->id);
	}
	else
		sem_post(philo->last_meal_sem);
}

//Function that monitors the status of the philosophers
void	*monitoring(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	while (1)
	{
		if (philo->n_times_eat > -1)
			check_if_meals_eaten(philo);
		check_if_dead(philo);
		usleep(200);
	}
	return (NULL);
}
