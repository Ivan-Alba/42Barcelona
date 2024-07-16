/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:07:53 by igarcia2          #+#    #+#             */
/*   Updated: 2024/07/16 12:07:55 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//Check if the philosophers have taken the necessary amount of meals
void	check_if_meals_eaten(t_data *data)
{
	int	i;
	int	philos_done;

	philos_done = 0;
	i = -1;
	while (++i < data->philo_num)
	{
		pthread_mutex_lock(&(data->philos[i].meals_eaten_lock));
		if (data->philos[i].meals_eaten >= data->philos[i].n_times_eat)
			philos_done++;
		pthread_mutex_unlock(&(data->philos[i].meals_eaten_lock));
		if (i + 1 == data->philo_num)
		{
			if (philos_done == data->philo_num)
			{
				pthread_mutex_lock(&(data->dead_lock));
				data->dead_flag = 1;
				pthread_mutex_unlock(&(data->dead_lock));
			}
		}
	}
}

//Check if any philosopher dies 
void	check_if_dead(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_num)
	{
		pthread_mutex_lock(&(data->philos[i].meal_lock));
		if (get_time_ms() - data->philos[i].last_meal
			> data->philos[i].die_time)
		{
			pthread_mutex_unlock(&(data->philos[i].meal_lock));
			pthread_mutex_lock(&(data->dead_lock));
			data->dead_flag = 1;
			pthread_mutex_unlock(&(data->dead_lock));
			print_log("is dead", get_time_ms(), &(data->philos[i]));
			break ;
		}
		pthread_mutex_unlock(&(data->philos[i].meal_lock));
	}
}

//Function that monitors the status of the philosophers
void	monitoring(t_data *data)
{
	int	i;

	while (1)
	{
		check_if_dead(data);
		if (data->philos[0].n_times_eat > 0)
			check_if_meals_eaten(data);
		pthread_mutex_lock(&(data->dead_lock));
		if (data->dead_flag == 1)
		{
			pthread_mutex_unlock(&(data->dead_lock));
			break ;
		}
		pthread_mutex_unlock(&(data->dead_lock));
		usleep(200);
	}
	i = -1;
	while (++i < data->philo_num)
		pthread_join(data->philos[i].thread, NULL);
}
