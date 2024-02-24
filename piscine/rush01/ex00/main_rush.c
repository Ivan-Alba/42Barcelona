/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_rush.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josegar2 <josegar2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 21:53:06 by josegar2          #+#    #+#             */
/*   Updated: 2023/10/29 21:13:29 by josegar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	insert_numbers(int size, char elmapa[11][11]);

int		rellena_mapa(char elmapa[11][11], int size);

void	reset_map(int size, char elmapa[11][11]);

int		ft_check_args(int argc, char *argv[], char elmapa[11][11]);

void	print_mapa(char elmapa[11][11], int size)
{
	int		row;
	int		col;
	char	digit;

	row = 1;
	while (row <= size)
	{
		col = 1;
		while (col <= size)
		{
			digit = elmapa[col][row] + '0';
			write(1, &digit, 1);
			if (col < size)
			{
				write(1, " ", 1);
			}
			col++;
		}
		write(1, "\n", 1);
		row++;
	}
}

void	print_mapa_total(char elmapa[11][11], int size)
{
	int		row;
	int		col;
	char	digit;

	row = 0;
	while (row <= size + 1)
	{
		col = 0;
		while (col <= size + 1)
		{
			digit = elmapa[col][row] + '0';
			write(1, &digit, 1);
			if (col < size + 1)
			{
				write(1, " ", 1);
			}
			col++;
		}
		write(1, "\n", 1);
		row++;
	}
}

int	main(int argc, char *argv[])
{
	char	mapa[11][11];
	int		size;

	reset_map(11, mapa);
	size = ft_check_args(argc, argv, mapa);
	if (size == 0)
	{
		write(1, "Error\n", 6);
		return (1);
	}
	insert_numbers(size, mapa);
	if (rellena_mapa(mapa, size) == 1)
	{
		write(1, "Error\n", 6);
		return (1);
	}
	print_mapa(mapa, size);
}
