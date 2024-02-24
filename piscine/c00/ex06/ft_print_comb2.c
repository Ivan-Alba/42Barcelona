/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_comb2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 11:12:57 by igarcia2          #+#    #+#             */
/*   Updated: 2023/10/24 15:23:46 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	write_numbers(int dec1, int uni1, int dec2, int uni2)
{
	write(1, &dec1, 1);
	write(1, &uni1, 1);
	write(1, " ", 1);
	write(1, &dec2, 1);
	write(1, &uni2, 1);
	if (dec1 < '9' || uni1 < '8')
	{
		write(1, ", ", 2);
	}
}

void	second_number_loop(int digits[])
{
	while (digits[2] < '9' || digits[3] < '9')
	{
		write_numbers(digits[0], digits[1], digits[2], digits[3]);
		if (digits[3] == '9')
		{
			digits[2]++;
			digits[3] = '0';
		}
		else
		{
			digits[3]++;
		}
	}
}

void	number_conditions(int digits[])
{
	if (digits[1] == '9')
	{
		digits[0]++;
		digits[1] = '0';
		digits[2] = digits[0];
		digits[3] = digits[1] + 1;
	}
	else
	{
		digits[1]++;
	}
	if (digits[1] == '9')
	{
		digits[2] = digits[0] + 1;
		digits[3] = '0';
	}
	else
	{
		digits[2] = digits[0];
		digits[3] = digits[1] + 1;
	}
}

void	ft_print_comb2(void)
{
	int		digits[4];

	digits[0] = '0';
	digits[1] = '0';
	digits[2] = '0';
	digits[3] = '1';
	while (digits[0] < '9' || digits[1] < '8')
	{
		second_number_loop(digits);
		write_numbers(digits[0], digits[1], digits[2], digits[3]);
		number_conditions(digits);
	}
	write_numbers(digits[0], digits[1], digits[2], digits[3]);
}
