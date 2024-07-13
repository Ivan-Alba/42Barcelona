/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 03:50:29 by igarcia2          #+#    #+#             */
/*   Updated: 2024/07/13 17:09:16 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <limits.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>
# include <semaphore.h>
# include <pthread.h>
# include <signal.h>
# include <fcntl.h>

typedef struct s_philo
{
	pthread_t		thread;
	int		id;
	int		pid;
	int		done;
	int		meals_eaten;
	long	last_meal;
	long	die_time;
	long	eat_time;
	long	sleep_time;
	long	act_time;
	int		n_times_eat;
	int		dead;
	int		*dead_flag;
	long	*start;
	sem_t	*forks_sem;
	sem_t	*write_sem;
	sem_t	*meals_eaten_sem;
	sem_t	*last_meal_sem;
	sem_t	*dead_sem;
	sem_t	*done_sem;
	sem_t	*dead_flag_sem;
}	t_philo;

typedef struct s_data
{
	int		dead_flag;
	int		philo_num;
	long	start_time;
	int		dead_written;
	sem_t	*forks_sem;
	sem_t	*dead_flag_sem;
	sem_t	*write_sem;
	sem_t	*start_sem;
	t_philo	*philos;
}	t_data;

int		ft_strlen(char *str);
int		ft_strncmp(const char *s1, const char *s2);
void	print_error(char *str, t_data *data);
void	free_data(t_data *data);
long	get_time_ms(void);
int		philos_start(t_data *data);
void	*monitoring(void *param);
//Actions
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);
void	print_log(char *message, long action_time, t_philo *philo);

#endif
