/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxiliar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 12:29:49 by igarcia2          #+#    #+#             */
/*   Updated: 2023/10/29 12:56:23 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	print_numbers(int size, char numbers[11][11])
{
	int	x;
	int	y;

	x = 1;
	y = 1;
	while (x <= size)
	{
		while (y <= size)
		{
			ft_putchar(numbers[y][x] + '0');
			y++;
			if (y <= size)
				write(1, " ", 1);
		}
		y = 1;
		x++;
		write(1, "\n", 1);
	}
}
