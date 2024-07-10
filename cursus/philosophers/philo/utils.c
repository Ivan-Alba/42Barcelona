/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 03:59:20 by igarcia2          #+#    #+#             */
/*   Updated: 2024/07/10 15:51:51 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	print_error(char *str, t_data *data)
{
	write(2, str, ft_strlen(str));
	if (data)
		free_data(data);
}

void	free_data(t_data *data)
{
	if (data)
	{
		if (data->philos)
		{
			free(data->philos);
		}
		free(data);
	}
}

int	ft_strncmp(const char *s1, const char *s2)
{
	unsigned char	*c1;
	unsigned char	*c2;
	int				i;

	i = 0;
	c1 = (unsigned char *) s1;
	c2 = (unsigned char *) s2;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return (c1[i] - c2[i]);
}

//Function that obtains the milliseconds elapsed since 1970-01-01
long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000L) + (tv.tv_usec / 1000L));
}
