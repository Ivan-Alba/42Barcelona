/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:39:14 by igarcia2          #+#    #+#             */
/*   Updated: 2023/11/09 17:44:03 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

char	*put_on_malloc(char *array, int count)
{
	int		i;
	char	*result;
	int		j;

	i = 0;
	j = 0;
	result = (char *) malloc((count + 1) * sizeof(char));
	if (result == NULL)
		return (result);
	if (array[0] == '-')
		result[i++] = '-';
	while (i < count)
		result[i++] = array[count - j++ - 1];
	result[i] = '\0';
	return (result);
}

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

int	transform_to_base(char *array, int count, int nbr, char *base)
{
	int	size;

	size = check_base(base);
	if (nbr == 0)
	{
		array[count++] = base[0];
	}
	while (nbr != 0)
	{
		array[count++] = base[nbr % size];
		nbr /= size;
	}
	return (count);
}

char	*ft_putnbr_base(int nbr, char *base)
{
	int		count;
	int		size;
	char	array[200];

	count = 0;
	size = check_base(base);
	if (!size || size < 2)
		return (NULL);
	if (nbr < 0)
	{
		array[count++] = '-';
		if (nbr == -2147483648)
		{
			array[count++] = base[-(nbr % size)];
			nbr /= size;
			nbr = -nbr;
		}
		else
			nbr = -nbr;
	}
	count = transform_to_base(array, count, nbr, base);
	return (put_on_malloc(array, count));
}
