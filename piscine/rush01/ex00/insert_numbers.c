/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 14:44:50 by igarcia2          #+#    #+#             */
/*   Updated: 2023/10/29 20:38:11 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c);
void	print_numbers(int size, char numbers[11][11]);

void	four_founded(int crr[3], int size, char map[11][11])
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (crr[2] == 0)
			map[crr[0]][crr[1] + i] = i + 1;
		if (crr[2] == 1)
			map[crr[0]][crr[1] - i] = i + 1;
		if (crr[2] == 2)
			map[crr[0] + i][crr[1]] = i + 1;
		if (crr[2] == 3)
			map[crr[0] - i][crr[1]] = i + 1;
		i++;
	}
}

void	move_position_on_map(int crr[3], int size, int count)
{
	if (crr[2] == 0 || crr[2] == 1)
		crr[0]++;
	else if (crr[2] == 2 || crr[2] == 3)
		crr[1]++;
	if (count % size == 0 && count / size == 1)
	{
		crr[0] = 1;
		crr[1] = size;
		crr[2] = 1;
	}
	else if (count % size == 0 && count / size == 2)
	{
		crr[0] = 1;
		crr[1] = 1;
		crr[2] = 2;
	}
	else if (count % size == 0 && count / size == 3)
	{
		crr[0] = size;
		crr[1] = 1;
		crr[2] = 3;
	}
}

int	check_from_values(int size, char map[11][11], char *values)
{
	int		count;
	int		crr[3];

	crr[0] = 1;
	crr[1] = 1;
	crr[2] = 0;
	count = 0;
	while (count < size * 4)
	{
		if (values[count] == size)
		{
			four_founded(crr, size, map);
		}
		else if (values[count] == 1)
		{
			if (map[crr[0]][crr[1]] != size && map[crr[0]][crr[1]] != 0)
				return (1);
			else
				map[crr[0]][crr[1]] = size;
		}
		count++;
		move_position_on_map(crr, size, count);
	}
	return (0);
}

void	change_position_to_read(int size, int count, int coord[2])
{
	if (count % size == 0 && count / size == 1)
	{
		coord[0] = 1;
		coord[1] = size + 1;
	}
	else if (count % size == 0 && count / size == 2)
	{
		coord[0] = 0;
		coord[1] = 1;
	}
	else if (count % size == 0 && count / size == 3)
	{
		coord[0] = size + 1;
		coord[1] = 1;
	}
	else if (count < 8)
		coord[0]++;
	else
		coord[1]++;
}

int	insert_numbers(int size, char map[11][11])
{
	int		coord[2];
	int		count;
	char	values[36];

	count = 0;
	coord[0] = 1;
	coord[1] = 0;
	while (count < (size * 4))
	{
		values[count] = map[coord[0]][coord[1]];
		count++;
		change_position_to_read(size, count, coord);
	}
	if (check_from_values(size, map, values))
		return (1);
	return (0);
}
