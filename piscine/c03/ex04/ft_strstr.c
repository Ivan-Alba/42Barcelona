/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:49:52 by igarcia2          #+#    #+#             */
/*   Updated: 2023/10/26 18:23:46 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

char	*ft_strstr(char *str, char *to_find)
{
	int	i;
	int	size;
	int	j;

	size = 0;
	i = 0;
	while (to_find[size] != '\0')
	{
		size++;
	}
	if (size == 0)
		return (str);
	while (str[i] != '\0')
	{
		j = 0;
		while (to_find[j] == str[i + j] && j < size)
		{
			if (j == size - 1)
				return (str + i);
			j++;
		}
		i++;
	}
	return (0);
}
