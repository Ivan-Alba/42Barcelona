/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 19:09:53 by igarcia2          #+#    #+#             */
/*   Updated: 2023/11/06 19:28:59 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	*ft_range(int min, int max)
{
	int	*array;
	int	i;

	i = 0;
	if (min >= max)
		array = NULL;
	else
	{
		array = (int *) malloc((max - min) * sizeof(int));
		if (array == NULL)
			return (array);
		while (min + i < max)
		{
			array[i] = min + i;
			i++;
		}
	}
	return (array);
}
