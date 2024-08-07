/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 03:47:11 by igarcia2          #+#    #+#             */
/*   Updated: 2024/08/07 12:46:14 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//Link philosophers forks to l_fork pointer
void	init_forks(t_data *data)
{
	int	i;

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
}

//Initializes the data of the structures
void	init_data(t_data *data, int argc, char **argv)
{
	int	i;

	i = -1;
	while (++i < data->philo_num)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal = get_time_ms();
		data->philos[i].die_time = check_int(argv[2]);
		data->philos[i].eat_time = check_int(argv[3]);
		data->philos[i].sleep_time = check_int(argv[4]);
		data->philos[i].dead = &(data->dead_flag);
		data->philos[i].start = &(data->start_time);
		data->philos[i].write_lock = &(data->write_lock);
		data->philos[i].dead_lock = &(data->dead_lock);
		data->philos[i].start_lock = &(data->start_lock);
		pthread_mutex_init(&(data->philos[i].meal_lock), NULL);
		pthread_mutex_init(&(data->philos[i].meals_eaten_lock), NULL);
		pthread_mutex_init(&(data->philos[i].r_fork), NULL);
		if (argc == 6 && argv[5][0] != '\0')
			data->philos[i].n_times_eat = check_int(argv[5]);
		else
			data->philos[i].n_times_eat = -1;
	}
	init_forks(data);
}

//Main function
int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc < 5 || argc > 6)
		return (print_error(ARGS_NUM_ERROR, NULL), 1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (print_error(MALLOC_ERROR, NULL), 1);
	if (check_args(argc, argv, data) == 1)
		return (print_error(ARGS_ERROR, data), 1);
	if (check_min_values(data))
		return (print_error(MIN_VALUES_ERROR, data), 1);
	philos_start(data);
	free_data(data);
	return (0);
}
