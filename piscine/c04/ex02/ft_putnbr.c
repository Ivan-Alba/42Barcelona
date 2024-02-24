/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 20:31:32 by igarcia2          #+#    #+#             */
/*   Updated: 2023/10/26 21:28:49 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putnbr(int nb)
{
	char				array[20];
	unsigned int		number;
	int					i;

	if (nb == 0)
		write(1, "0", 1);
	else
	{
		i = 0;
		if (nb < 0)
		{
			write(1, "-", 1);
			number = -nb;
		}
		else
			number = nb;
		while (number > 0)
		{
			array[i++] = number % 10 + '0';
			number /= 10;
		}
		while (i-- > 0)
			write(1, &array[i], 1);
	}
}
