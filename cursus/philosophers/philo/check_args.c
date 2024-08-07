/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 12:26:32 by igarcia2          #+#    #+#             */
/*   Updated: 2024/08/07 12:43:05 by igarcia2         ###   ########.fr       */
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

//Checks the arguments and calls the necessary functions to store the data
int	check_args(int argc, char **argv, t_data *data)
{
	data->philo_num = check_int(argv[1]);
	if (!data->philo_num)
		return (1);
	data->dead_flag = 0;
	data->philos = malloc(data->philo_num * sizeof(t_philo));
	if (!data->philos)
		return (print_error(MALLOC_ERROR, data), 2);
	init_data(data, argc, argv);
	if (!data->philos[0].die_time || !data->philos[0].eat_time
		|| !data->philos[0].sleep_time || !data->philos[0].n_times_eat)
		return (1);
	return (0);
}

int	check_min_values(t_data *data)
{
	if (data->philos[0].die_time < 60 || data->philos[0].eat_time < 60
		|| data->philos[0].sleep_time < 60)
		return (1);
	return (0);
}
