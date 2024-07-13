/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 03:47:11 by igarcia2          #+#    #+#             */
/*   Updated: 2024/07/13 17:16:19 by igarcia2         ###   ########.fr       */
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

void	init_philos_sem(t_philo *philo)
{
	philo->meals_eaten_sem = sem_open("/meals_eaten_sem", O_CREAT, 0644, 1);
	philo->last_meal_sem = sem_open("/last_meal_sem", O_CREAT, 0644, 1);
 	philo->dead_sem = sem_open("/dead_sem", O_CREAT, 0644, 1);
	philo->done_sem = sem_open("/done_sem", O_CREAT, 0644, 1);
}

//Initializes the data of the structures
void	init_data(t_data *data, int argc, char **argv)
{
	int	i;

	sem_unlink("/meals_eaten_sem");
	sem_unlink("/last_meal_sem");
	sem_unlink("/dead_sem");
	sem_unlink("/done_sem");
	sem_unlink("/forks_sem");
	sem_unlink("/write_sem");
	sem_unlink("/start_sem");
	sem_unlink("/dead_flag_sem");
	data->dead_flag = 0;
	data->forks_sem = sem_open("/forks_sem", O_CREAT, 0644, data->philo_num);
	data->write_sem = sem_open("/write_sem", O_CREAT, 0644, 1);
	data->start_sem = sem_open("/start_sem", O_CREAT, 0644, 1);
	data->dead_flag_sem = sem_open("/dead_flag_sem", O_CREAT, 0644, 1);
	i = -1;
	while (++i < data->philo_num)
	{
		data->philos[i].id = i + 1;
		data->philos[i].pid = -1;
		data->philos[i].done = 0;
		data->philos[i].meals_eaten = 0;
		data->philos[i].n_times_eat = -1;
		data->philos[i].last_meal = get_time_ms();
		data->philos[i].die_time = check_int(argv[2]);
		data->philos[i].eat_time = check_int(argv[3]);
		data->philos[i].sleep_time = check_int(argv[4]);
		data->philos[i].dead = 0;
		data->philos[i].dead_flag = &(data->dead_flag);
		data->philos[i].dead_flag_sem = data->dead_flag_sem;
		data->philos[i].start = &(data->start_time);
		data->philos[i].forks_sem = data->forks_sem;
		data->philos[i].write_sem = data->write_sem;
		init_philos_sem(&(data->philos[i]));
		if (argc == 6 && argv[5][0] != '\0')
			data->philos[i].n_times_eat = check_int(argv[5]);
	}
}

//Checks the arguments and calls the necessary functions to store the data
int	check_args(int argc, char **argv, t_data *data)
{
	if (argc < 5 || argc > 6)
		return (1);
	data->philo_num = check_int(argv[1]);
	if (!data->philo_num)
		return (1);
	data->dead_flag = 0;
	data->philos = malloc(data->philo_num * sizeof(t_philo));
	if (!data->philos)
		return (print_error("MALLOC ERROR\n", data), 2);
	init_data(data, argc, argv);
	if (!data->philos[0].die_time || !data->philos[0].eat_time
		|| !data->philos[0].sleep_time || !data->philos[0].n_times_eat)
		return (1);
	return (0);
}

void	status_info(int	status)
{
 if (WIFEXITED(status)) {
            printf("El proceso hijo terminó normalmente.\n");
            int exit_status = WEXITSTATUS(status);
            printf("Estado de salida del hijo: %d\n", exit_status);
        } else if (WIFSIGNALED(status)) {
            printf("El proceso hijo terminó debido a una señal.\n");
            int term_signal = WTERMSIG(status);
            printf("Señal que terminó el hijo: %d\n", term_signal);
        } else {
            printf("El proceso hijo terminó de manera anormal.\n");
        }
}

void	kill_all_proccesses(t_data *data, int error_code)
{
	int	i;

	i = -1;
	while (++i < data->philo_num)
	{
		if (i + 1 != error_code)
			kill(data->philos[i].pid, SIGKILL);
	}
}

//Main function
int	main(int argc, char **argv)
{
	t_data	*data;
	int		child_remaining;
	int		status;

	data = malloc(sizeof(t_data));
	if (!data)
		return (print_error("MALLOC ERROR\n", NULL), 1);
	if (check_args(argc, argv, data) == 1)
		return (print_error("ARGS ERROR\n", data), 1);
	if (philos_start(data))
		return (print_error("Error creating proccesses\n", data), 1);
 
	//WAIT FOR CHILDREN
	child_remaining = data->philo_num;
	while (child_remaining > 0)
	{
			waitpid(-1, &status, 0);
			if (WIFEXITED(status) && WEXITSTATUS(status) > 0)
			{
				kill_all_proccesses(data, WEXITSTATUS(status));
				break ;
			}	
			//status_info(status);
			child_remaining--;
	}
	free_data(data);
	return (0);
}
