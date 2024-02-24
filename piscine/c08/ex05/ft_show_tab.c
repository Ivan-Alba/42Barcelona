/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_show_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:57:01 by igarcia2          #+#    #+#             */
/*   Updated: 2023/11/09 18:01:59 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_stock_str.h"

char	*ft_putnbr(int nb, int *size)
{
	static char				array[20];
	unsigned int			number;
	int						i;
	int						idx_rev;
	char					c;

	i = 0;
	number = nb;
	while (number > 0)
	{
		array[i++] = number % 10 + '0';
		number /= 10;
	}
	*size = i;
	idx_rev = i - 1;
	i = 0;
	while (i < *size / 2)
	{
		c = array[i];
		array[i] = array[idx_rev - i];
		array[idx_rev - i] = c;
		i++;
	}
	return (array);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	ft_show_tab(struct s_stock_str *par)
{
	int		i;
	int		array_size;
	char	*size;

	array_size = 0;
	i = 0;
	while (par[i].str != 0)
	{
		write(1, par[i].str, ft_strlen(par[i].str));
		write(1, "\n", 1);
		size = ft_putnbr(par[i].size, &array_size);
		write(1, size, ft_strlen(size));
		write(1, "\n", 1);
		write(1, par[i].copy, ft_strlen(par[i].copy));
		write(1, "\n", 1);
		i++;
	}
}
