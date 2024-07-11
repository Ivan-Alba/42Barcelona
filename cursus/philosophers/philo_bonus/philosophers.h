/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 03:50:29 by igarcia2          #+#    #+#             */
/*   Updated: 2024/07/11 15:53:10 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <limits.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdio.h>
# include <semaphore.h>
//# include <pthread.h>

typedef struct s_philo
{
	//pthread_t		thread;
	int		id;
	int		meals_eaten;
	long	last_meal;
	long	die_time;
	long	eat_time;
	long	sleep_time;
	long	act_time;
	int		n_times_eat;
	int		dead;
	long	*start;
	sem_t	*sem;
}	t_philo;

typedef struct s_data
{
	int		dead_flag;
	int		philo_num;
	long	start_time;
	sem_t	sem;
	t_philo	*philos;
}	t_data;

int		ft_strlen(char *str);
int		ft_strncmp(const char *s1, const char *s2);
void	print_error(char *str, t_data *data);
void	free_data(t_data *data);
long	get_time_ms(void);
int		philos_start(t_data *data);
void	monitoring(t_data *data);
//Actions
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);
void	print_log(char *message, long action_time, t_philo *philo);

#endif
