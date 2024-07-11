/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 04:18:54 by igarcia2          #+#    #+#             */
/*   Updated: 2024/07/11 15:12:58 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//Function that prints on the screen the actions of the philosophers
void	print_log(char *txt, long action_time, t_philo *philo)
{
	int	dead;

	pthread_mutex_lock(philo->write_lock);
	pthread_mutex_lock(philo->dead_lock);
	dead = *philo->dead;
	pthread_mutex_unlock(philo->dead_lock);
	if (!dead || !ft_strncmp(txt, "is dead"))
		printf("%ld %d %s\n", action_time - *(philo->start), philo->id, txt);
	pthread_mutex_unlock(philo->write_lock);
}

//Function that manages the locking of the philosophers' forks
void	lock_forks(t_philo *philo, int is_first_fork)
{
	if (is_first_fork)
	{
		if (philo->id % 2 == 0)
			pthread_mutex_lock(philo->l_fork);
		else
			pthread_mutex_lock(&(philo->r_fork));
		print_log("has taken a fork", get_time_ms(), philo);
	}
	else
	{
		if (philo->id % 2 == 0)
			pthread_mutex_lock(&(philo->r_fork));
		else
			pthread_mutex_lock(philo->l_fork);
		print_log("has taken a fork", get_time_ms(), philo);
	}
}

//Function that manages the philosophers' eating action
void	philo_eat(t_philo *philo)
{
	lock_forks(philo, 1);
	if (philo->l_fork)
	{
		lock_forks(philo, 0);
		pthread_mutex_lock(&(philo->meal_lock));
		philo->act_time = get_time_ms();
		philo->last_meal = philo->act_time;
		pthread_mutex_unlock(&(philo->meal_lock));
		print_log("is eating", philo->act_time, philo);
		while (1)
		{
			if (get_time_ms() - philo->act_time >= philo->eat_time)
				break ;
		}
		pthread_mutex_unlock(&(philo->r_fork));
		pthread_mutex_unlock(philo->l_fork);
	}
	else
		pthread_mutex_unlock(&(philo->r_fork));
}

//Function that manages the philosophers' sleeping action
void	philo_sleep(t_philo *philo)
{
	if (philo->l_fork)
	{
		philo->act_time = get_time_ms();
		print_log("is sleeping", philo->act_time, philo);
		while (1)
		{
			if (get_time_ms() - philo->act_time >= philo->sleep_time)
				break ;
		}
	}
	else
		usleep(philo->die_time * 1001);
}

//Function that manages the philosophers' thinking action
void	philo_think(t_philo *philo)
{
	if (philo->l_fork)
	{
		philo->act_time = get_time_ms();
		print_log("is thinking", philo->act_time, philo);
	}
}
