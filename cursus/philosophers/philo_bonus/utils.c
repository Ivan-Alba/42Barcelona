/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 03:59:20 by igarcia2          #+#    #+#             */
/*   Updated: 2024/07/13 14:18:21 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//Receives a char * as argument and returns the character length
int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

//Prints the message received by parameter on the error fd and frees the data
void	print_error(char *str, t_data *data)
{
	if (str)
		write(2, str, ft_strlen(str));
	if (data)
		free_data(data);
}

//Frees data from structures
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

//Compares two strings and returns 0 if equal
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
