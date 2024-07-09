/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 04:18:54 by igarcia2          #+#    #+#             */
/*   Updated: 2024/07/09 15:05:18 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_log(char *txt, long action_time, t_philo *philo)
{
	int	dead;

	pthread_mutex_lock(philo->write_lock);
	pthread_mutex_lock(philo->dead_lock);
	dead = *philo->dead;
	pthread_mutex_unlock(philo->dead_lock);
	if (!dead || !ft_strncmp(message, "is dead"))
		printf("%ld %d %s\n", action_time - *(philo->start), philo->id, txt);
	pthread_mutex_unlock(philo->write_lock);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&(philo->r_fork));
	print_log("has taken a fork", get_time_in_milliseconds(), philo);
	if (philo->l_fork)
	{
		pthread_mutex_lock(philo->l_fork);
		print_log("has taken a fork", get_time_in_milliseconds(), philo);
		pthread_mutex_lock(&(philo->meal_lock));
		philo->start_time = get_time_in_milliseconds();
		philo->last_meal = philo->start_time;
		pthread_mutex_unlock(&(philo->meal_lock));
		print_log("is eating", philo->start_time, philo);
		while (1)
		{
			if (get_time_in_milliseconds() - philo->start_time >= philo->time_to_eat)
				break ;
		}
		pthread_mutex_unlock(&(philo->r_fork));
		pthread_mutex_unlock(philo->l_fork);
	}
	else
	{
		pthread_mutex_unlock(&(philo->r_fork));
		usleep(philo->time_to_die * 1000);
	}
}

void	philo_sleep(t_philo *philo)
{
	philo->start_time = get_time_in_milliseconds();
	print_log("is sleeping", philo->start_time, philo);
	while (1)
	{
		if (get_time_in_milliseconds() - philo->start_time >= philo->time_to_sleep)
			break ;
	}
}

void	philo_think(t_philo *philo)
{
	philo->start_time = get_time_in_milliseconds();
	print_log("is thinking", philo->start_time, philo);
}
