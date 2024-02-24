/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush00.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 00:50:45 by igarcia2          #+#    #+#             */
/*   Updated: 2023/10/22 01:21:57 by igarcia2         ###   ########.fr       */
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
	xc = 1;
	print_error(x, y);
	while (yc <= y)
	{
		while (xc <= x)
		{
			if ((yc == 1 || yc == y) && (xc == 1 || xc == x))
				ft_putchar('o');
			else if ((yc == 1 || yc == y) && (xc > 1 && xc < x))
				ft_putchar('-');
			else if ((xc == 1 || xc == x) && (yc > 1 && yc < y))
				ft_putchar('|');
			else
				ft_putchar(' ');
			xc++;
		}
		ft_putchar('\n');
		xc = 1;
		yc++;
	}
}
