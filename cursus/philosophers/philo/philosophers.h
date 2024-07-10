/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 03:50:29 by igarcia2          #+#    #+#             */
/*   Updated: 2024/07/10 15:52:29 by igarcia2         ###   ########.fr       */
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

int		ft_strlen(char *str);
int		ft_strncmp(const char *s1, const char *s2);
void	print_error(char *str, t_data *data);
void	free_data(t_data *data);
long	get_time_ms(void);
void	philos_start(t_data *data);
void	monitoring(t_data *data);
//Actions
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);
void	print_log(char *message, long action_time, t_philo *philo);

#endif
