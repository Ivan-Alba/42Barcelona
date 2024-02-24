/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush01.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 11:46:56 by akozin            #+#    #+#             */
/*   Updated: 2023/10/21 15:18:13 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c);

void	print_error(int x, int y)
{
	if (x < 1 || y < 1)
		write(1, "Error", 5);
}

void	rush(int x, int y)
{
	int	xc;
	int	yc;

	yc = 1;
	print_error(x, y);
	while (yc <= y)
	{
		xc = 1;
		while (xc <= x)
		{
			if ((x == 1 && y > 1 && yc == y) || (y == 1 && x > 1 && xc == x))
				ft_putchar('\\');
			else if ((xc == 1 && yc == 1) || (xc == x && yc == y))
				ft_putchar('/');
			else if ((xc == 1 && yc == y) || (xc == x && yc == 1))
				ft_putchar('\\');
			else if (xc == 1 || xc == x || yc == 1 || yc == y)
				ft_putchar('*');
			else
				ft_putchar(' ');
			xc++;
		}
		ft_putchar('\n');
		yc++;
	}
}
