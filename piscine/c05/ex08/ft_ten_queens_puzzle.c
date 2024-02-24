/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 21:13:25 by igarcia2          #+#    #+#             */
/*   Updated: 2023/11/02 21:20:58 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	g_count = 0;

int	ft_putnbr(int nb)
{
	long	num;
	char	c;

	num = nb;
	if (num < 0)
	{
		num *= -1;
		write(1, "-", 1);
	}
	if (num > 9)
		ft_putnbr(num / 10);
	c = (num % 10 + 48);
	write(1, &c, 1);
	return (num);
}

void	print_board(int *board)
{
	int	col;

	col = 0;
	while (col < 10)
	{
		ft_putnbr(board[col]);
		col++;
	}
	write(1, "\n", 1);
}

int	check_board(int *board, int current)
{
	int	i;

	i = 0;
	while (i < current)
	{
		if (board[i] == board[current])
			return (0);
		if (board[i] == board[current] + (current - i)
			|| board[i] == board[current] - (current - i))
			return (0);
		i++;
	}
	return (1);
}

void	try_queens(int *board, int current)
{
	int	i;

	if (current == 10)
	{
		print_board(board);
		g_count++;
		return ;
	}
	else
	{
		i = 0;
		while (i < 10)
		{
			board[current] = i;
			if (check_board(board, current))
			{
				try_queens(board, current + 1);
			}
			i++;
		}
	}
}

int	ft_ten_queens_puzzle(void)
{
	int	board[10];

	try_queens(board, 0);
	return (g_count);
}
