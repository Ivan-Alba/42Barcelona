/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 13:36:39 by igarcia2          #+#    #+#             */
/*   Updated: 2023/11/02 17:58:58 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	check_base(char *base)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (base[i] != '\0')
	{
		if (base[i] == '+' || base[i] == '-'
			|| base[i] <= 32 || base [i] >= 127)
			return (0);
		while (base[j] != '\0')
		{
			if (base[i] == base[j])
				return (0);
			j++;
		}
		i++;
		j = i + 1;
	}
	if (i < 2)
		return (0);
	return (i);
}

void	transform_to_base(char *array, int count, int nbr, char *base)
{
	int	size;

	size = check_base(base);
	while (nbr != 0)
	{
		array[count++] = base[nbr % size];
		nbr /= size;
	}
	while (count > 0)
		write(1, &array[count-- -1], 1);
}

void	ft_putnbr_base(int nbr, char *base)
{
	int		count;
	int		size;
	char	array[200];

	count = 0;
	size = check_base(base);
	if (!size)
		return ;
	if (nbr < 0)
	{
		write(1, "-", 1);
		if (nbr == -2147483648)
		{
			array[count++] = base[-(nbr % size)];
			nbr /= size;
			nbr = -nbr;
		}
		else
			nbr = -nbr;
	}
	if ((size == 2 && nbr == 0) || nbr == 0)
		write(1, "0", 1);
	transform_to_base(array, count, nbr, base);
}
