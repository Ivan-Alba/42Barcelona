/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 03:47:11 by igarcia2          #+#    #+#             */
/*   Updated: 2024/05/18 04:49:06 by igarcia2         ###   ########.fr       */
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
	if (argc < 5 || argc > 6)
		return (1);
	data->philo_num = check_int(argv[1]);
	data->die_time = check_int(argv[2]);
	data->eat_time = check_int(argv[3]);
	data->sleep_time = check_int(argv[4]);
	if (argc == 6 && argv[5][0] != '\0')
		data->must_eat = check_int(argv[5]);
	else
		data->must_eat = -1;
	if (!data->philo_num || !data->die_time || !data->eat_time
		|| !data->sleep_time || !data->must_eat)
		return (1);
	return (0);
}

//Function that obtains the milliseconds elapsed since 1970-01-01
long	get_time_in_milliseconds(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000L) + (tv.tv_usec / 1000L));
}

//Main function
int	main(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (print_error("MALLOC ERROR\n", NULL), 1);
	if (check_args(argc, argv, data))
		return (print_error("ARGS ERROR\n", data), 1);
	free(data);
	printf("%ld\n", get_time_in_milliseconds());
	return (0);
}
