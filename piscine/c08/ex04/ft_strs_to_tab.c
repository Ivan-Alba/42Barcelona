/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strs_to_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 10:12:33 by igarcia2          #+#    #+#             */
/*   Updated: 2023/11/09 18:00:23 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_stock_str.h"

int	ft_strlen(char *str)
{
	int	count;

	count = 0;
	while (str[count] != '\0')
	{
		count++;
	}
	return (count);
}

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
		i++;
	}
	*dest = '\0';
	dest -= i;
	return (dest);
}

struct	s_stock_str	*ft_strs_to_tab(int ac, char **av)
{
	int					i;
	int					j;
	struct s_stock_str	*tab;
	char				*dest;

	i = 0;
	j = 0;
	tab = (struct s_stock_str *) malloc((ac + 1) * sizeof(struct s_stock_str));
	while (i < ac)
	{
		tab[i].size = ft_strlen(av[i]);
		tab[i].str = (char *) malloc(ft_strlen(av[i]) + 1);
		if (!tab[i].str)
			return (0);
		tab[i].str = av[i];
		dest = (char *) malloc(ft_strlen(tab[i].str) + 1);
		if (!dest)
			return (0);
		tab[i].copy = ft_strcpy(dest, tab[i].str);
		i++;
	}
	tab[i].str = (0);
	tab[i].copy = (0);
	return (tab);
}
