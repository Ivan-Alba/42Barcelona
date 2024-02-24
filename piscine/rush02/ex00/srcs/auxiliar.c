/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxiliar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 16:17:27 by igarcia2          #+#    #+#             */
/*   Updated: 2023/11/05 21:58:22 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

int		cifras(unsigned int n);
void	malloc_write(char *output, int number);
int		centenas(unsigned int numero, unsigned int base, int i, char *output);

int	ft_strlen(char *str)
{
	int	count;

	count = 0;
	while (str[count++] != '\0')
		str++;
	return (count);
}

int	ft_strcomp(char *s1, char *s2)
{
	while (*s1 != '\0' || *s2 != '\0')
	{
		if (*s1 == '\0')
			return (*s1 - *s2);
		else if (*s2 == '\0')
			return (*s1 - *s2);
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (0);
}

char	*ft_strstr(char *dict, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (to_find[j] == '\0')
		return (dict);
	while (dict[i] != '\0')
	{
		while (dict[i + j] == to_find[j] && dict[i + j] != '\0')
			j++;
		if (to_find[j] == '\0' && (dict[i + j] == ' ' || dict[i + j] == ':' ))
		{
			return (dict + i);
		}
		i++;
		j = 0;
	}
	return (0);
}

char	*ft_putnbr(int nb)
{
	char				*array;
	unsigned int		number;
	int					i;
	int					size;

	size = cifras(nb) + 1;
	array = (char *) malloc((size + 1) * sizeof(char));
	i = size - 2;
	if (nb < 0)
	{
		write(1, "-", 1);
		number = -nb;
	}
	else
		number = nb;
	while (number > 0)
	{
		array[i--] = number % 10 + '0';
		number /= 10;
	}
	array[size - 1] = '\0';
	return (array);
}

int	print_centenas(char *output, unsigned int base, unsigned int n, int i)
{
	malloc_write(output, n / base);
	malloc_write(output, base);
	n = n % base;
	base = base / 10;
	i -= 1;
	if (n != 0)
		centenas(n, base, i, output);
	return (i);
}
