/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 03:50:29 by igarcia2          #+#    #+#             */
/*   Updated: 2024/08/07 12:46:08 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <limits.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdio.h>
# include <pthread.h>

# define MIN_VALUES_ERROR "Times must be at least 60ms\n"
# define MALLOC_ERROR "Error allocating memory\n"
# define ARGS_NUM_ERROR "Error: there must be 4 or 5 numerical arguments\n"
# define ARGS_ERROR "Error: arguments must be numerical and cannot be 0\n"

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				meals_eaten;
	long			last_meal;
	long			die_time;
	long			eat_time;
	long			sleep_time;
	long			act_time;
	int				n_times_eat;
	int				*dead;
	long			*start;
	pthread_mutex_t	r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*start_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	meals_eaten_lock;
}	t_philo;

typedef struct s_data
{
	int				dead_flag;
	int				philo_num;
	long			start_time;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	start_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
}	t_data;

void	init_data(t_data *data, int argc, char **argv);
//check_args
int		check_int(char *arg);
int		check_args(int argc, char **argv, t_data *data);
int		check_min_values(t_data *data);
//utils
int		ft_strlen(char *str);
int		ft_strncmp(const char *s1, const char *s2);
void	print_error(char *str, t_data *data);
void	free_data(t_data *data);
long	get_time_ms(void);
//run
void	philos_start(t_data *data);
//monitor
void	monitoring(t_data *data);
//actions
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);
void	print_log(char *message, long action_time, t_philo *philo);

#endif
