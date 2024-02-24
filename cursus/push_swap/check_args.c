/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 16:05:26 by igarcia2          #+#    #+#             */
/*   Updated: 2024/02/23 19:20:38 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

//If we have any errors in the args we terminate the program
void	args_error(int **array)
{
	if (array && *array)
	{
		free(*array);
		*array = NULL;
	}
	write(2, ERROR_MSG, sizeof(ERROR_MSG));
	exit(0);
}

//Receives an arg, checks for correct formatting and transforms it to int
void	check_int(char *arg, int **array, int pos)
{
	long	num;
	int		sign;
	int		i;

	num = 0;
	sign = 1;
	i = 0;
	if (arg[i] == '-' || arg[i] == '+')
	{
		if (arg[i++] == '-')
			sign = -1;
	}
	if (arg[i] == '\0')
		args_error(array);
	while (arg[i] != '\0')
	{
		if (arg[i] < '0' || arg[i] > '9')
			args_error(array);
		num = num * 10 + (arg[i] - '0');
		i++;
		if (num * sign > INT_MAX || num * sign < INT_MIN)
			args_error(array);
	}
	num *= sign;
	(*array)[pos] = (int)num;
}

//Check that there are no duplicate integers
void	check_duplicate(int **array, int len)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < len)
	{
		j = i + 1;
		while (j < len)
		{
			if ((*array)[i] == (*array)[j])
				args_error(array);
			j++;
		}
		i++;
	}
}

//Function that checks if the args are ordered and exits the program
void	is_ordered(int **array, int count)
{
	int	i;

	i = 0;
	while (i < count - 1)
	{
		if ((*array)[i] > (*array)[i + 1])
			return ;
		i++;
	}
	free(*array);
	exit(0);
}

//Check args function
int	*check_args(int argc, char *argv[], int *count)
{
	int	i;
	int	*array;

	array = NULL;
	if (argc > 1)
	{
		i = 1;
		array = (int *)malloc((argc - 1) * sizeof(int));
		while (i < argc)
		{
			check_int(argv[i], &array, i - 1);
			i++;
		}
		check_duplicate(&array, argc - 1);
		*count = argc - 1;
		is_ordered(&array, *count);
	}
	return (array);
}
