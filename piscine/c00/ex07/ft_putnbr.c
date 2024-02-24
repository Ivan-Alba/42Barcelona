/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 13:44:03 by igarcia2          #+#    #+#             */
/*   Updated: 2023/10/22 13:19:12 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	initialize_array(char *array);
void	sort_array(char *array);
void	print_array_content(char *array, int last_number_at);

void	ft_putnbr(int value)
{
	long			u;
	char			c;
	char			array[20];
	int				array_pos;

	u = (long) value;
	if (value < 0)
	{
		u = -u;
		write(1, "-", 1);
	}
	initialize_array(array);
	array_pos = 0;
	while (u > 0)
	{
		c = u % 10 + '0';
		array[array_pos] = c;
		u = u / 10;
		array_pos++;
	}
	sort_array(array);
}

void	initialize_array(char *array)
{
	int	i;

	i = 0;
	while (i < 20)
	{
		array[i] = 'x';
		i++;
	}
}

void	sort_array(char *array)
{
	int		idx;
	int		rev_idx;
	int		last_number_at;
	char	aux;

	last_number_at = 0;
	while (last_number_at < 20)
	{
		if (array[last_number_at] != 'x')
			last_number_at++;
		else
			break ;
	}
	rev_idx = last_number_at;
	idx = 0;
	while (idx < last_number_at / 2)
	{
		aux = array[idx];
		array[idx] = array[rev_idx - 1];
		array[rev_idx - 1] = aux;
		idx++;
		rev_idx--;
	}
	print_array_content(array, last_number_at);
}

void	print_array_content(char *array, int last_number_at)
{
	int		i;
	char	c;

	i = 0;
	if (array[0] == 'x')
	{
		write(1, "0", 1);
		return ;
	}
	while (i < last_number_at)
	{
		c = array[i];
		write(1, &c, 1);
		i++;
	}
}
