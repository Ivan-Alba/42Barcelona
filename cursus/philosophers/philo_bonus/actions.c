/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 04:18:54 by igarcia2          #+#    #+#             */
/*   Updated: 2024/07/15 14:53:39 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//Function that prints on the screen the actions of the philosophers
void	print_log(char *txt, long action_time, t_philo *philo)
{
	sem_wait(philo->write_sem);
	printf("%ld %d %s\n", action_time - *(philo->start), philo->id, txt);
	if (ft_strncmp(txt, "is dead") != 0)
		sem_post(philo->write_sem);
}

//Function that manages the philosophers' eating action
void	philo_eat(t_philo *philo)
{
	sem_wait(philo->forks_sem);
	print_log("has taken a fork", get_time_ms(), philo);
	sem_wait(philo->forks_sem);
	print_log("has taken a fork", get_time_ms(), philo);
	sem_wait(philo->last_meal_sem);
	philo->act_time = get_time_ms();
	philo->last_meal = philo->act_time;
	sem_post(philo->last_meal_sem);
	print_log("is eating", philo->act_time, philo);
	while (1)
	{
		if (get_time_ms() - philo->act_time >= philo->eat_time)
			break ;
	}
	sem_post(philo->forks_sem);
	sem_post(philo->forks_sem);
	sem_wait(philo->meals_eaten_sem);
	philo->meals_eaten++;
	sem_post(philo->meals_eaten_sem);
}

//Function that manages the philosophers' sleeping action
void	philo_sleep(t_philo *philo)
{
	philo->act_time = get_time_ms();
	print_log("is sleeping", philo->act_time, philo);
	while (1)
	{
		if (get_time_ms() - philo->act_time >= philo->sleep_time)
			break ;
	}
}

//Function that manages the philosophers' thinking action
void	philo_think(t_philo *philo)
{
	philo->act_time = get_time_ms();
	print_log("is thinking", philo->act_time, philo);
}
