/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_combn.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 21:46:45 by igarcia2          #+#    #+#             */
/*   Updated: 2023/10/21 23:22:18 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_iteration(int n, int *array);
void	write_number(int *array, int n);
int		increase_previous(int n, int *max_reached, int *array);

void	ft_print_combn(int n)
{
	int	array[9];
	int	i;

	if (n > 0 && n < 10)
	{
		i = 0;
		while (i < n)
		{
			array[i] = i;
			i++;
		}
		write_number(array, n);
		ft_iteration(n, array);
	}
}

void	ft_iteration(int n, int *array)
{
	int	max_reached;
	int	max_number;

	max_reached = 0;
	max_number = 9 - max_reached;
	while (max_reached < n)
	{
		while (array[n - 1 - max_reached] < max_number)
		{
			array[n - 1 - max_reached]++;
			write_number(array, n);
		}
		if (n == 1)
			break ;
		max_reached++;
		max_number = 9 - max_reached;
		if (increase_previous(n, &max_reached, array) == 1)
			return ;
		max_number = 9 - max_reached;
	}
}

int	increase_previous(int n, int *max_reached, int *array)
{
	int	aux;
	int	max_number;

	aux = *max_reached;
	max_number = 9 - aux;
	if (array[n - 1 - aux] < max_number)
	{
		array[n - 1 - aux]++;
		while (aux != 0)
		{
			array[n - aux] = array[n - 1 - aux] + 1;
			aux--;
		}
		max_number = 9 - aux;
		write_number(array, n);
		if (array[0] == 10 - n)
		{
			*max_reached = aux;
			return (1);
		}
		*max_reached = aux;
	}
	return (0);
}

void	write_number(int *array, int n)
{
	int	i;
	int	number_to_print;

	i = 0;
	while (i < n)
	{
		number_to_print = array[i] + '0';
		write(1, &number_to_print, 1);
		i++;
	}
	if (array[0] != 10 - n)
		write(1, ", ", 2);
}
