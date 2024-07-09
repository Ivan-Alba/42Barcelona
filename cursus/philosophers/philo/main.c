/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 03:47:11 by igarcia2          #+#    #+#             */
/*   Updated: 2024/07/09 15:03:50 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//Receives an arg, checks for correct formatting and transforms it to int
int	check_int(char *arg)
{
	long	num;
	int		i;

	num = 0;
	i = 0;
	if (arg[i] == '-' || arg[i] == '+')
	{
		if (arg[i++] == '-')
			return (0);
	}
	if (arg[i] == '\0')
		return (0);
	while (arg[i] != '\0')
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (0);
		num = num * 10 + (arg[i] - '0');
		i++;
		if (num > INT_MAX || num < INT_MIN)
			return (0);
	}
	return ((int)num);
}

//Function that checks the args and stores them in the data structure.
int	check_args(int argc, char **argv, t_data *data)
{
	int	i;

	if (argc < 5 || argc > 6)
		return (1);
	data->philo_num = check_int(argv[1]);
	if (!data->philo_num)
		return (1);
	i = 0;
	data->dead_flag = 0;
	data->philos = malloc(data->philo_num * sizeof(t_philo));
	if (!data->philos)
		return (print_error("MALLOC ERROR\n", data), 2);
	while (i < data->philo_num)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal = get_time_in_milliseconds();
		data->philos[i].time_to_die = check_int(argv[2]);
		data->philos[i].time_to_eat = check_int(argv[3]);
		data->philos[i].time_to_sleep = check_int(argv[4]);
		data->philos[i].dead = &(data->dead_flag);
		data->philos[i].start = &(data->start_time);
		data->philos[i].write_lock = &(data->write_lock);
		data->philos[i].dead_lock = &(data->dead_lock);
		//data->philos[i].meal_lock = &(data->meal_lock);
		pthread_mutex_init(&(data->philos[i].meal_lock), NULL);
		pthread_mutex_init(&(data->philos[i].r_fork), NULL);
		if (argc == 6 && argv[5][0] != '\0')
			data->philos[i].num_times_to_eat = check_int(argv[5]);
		else
			data->philos[i].num_times_to_eat = -1;
		i++;
	}
	i = 0;
	while (i < data->philo_num)
	{
		if (i == 0)
		{
			if (data->philo_num == 1)
				data->philos[i].l_fork = NULL;
			else
				data->philos[i].l_fork = &(data->philos[data->philo_num - 1]
						.r_fork);
		}
		else
			data->philos[i].l_fork = &(data->philos[i - 1].r_fork);
		i++;
	}
	if (!data->philos[0].time_to_die || !data->philos[0].time_to_eat
		|| !data->philos[0].time_to_sleep || !data->philos[0].num_times_to_eat)
		return (1);
	return (0);
}

//Main function
int	main(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (print_error("MALLOC ERROR\n", NULL), 1);
	if (check_args(argc, argv, data) == 1)
		return (print_error("ARGS ERROR\n", data), 1);
	philos_start(data);
	free_data(data);
	return (0);
}
