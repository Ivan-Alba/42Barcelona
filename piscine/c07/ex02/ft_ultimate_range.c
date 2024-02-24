/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultimate_range.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 19:10:53 by igarcia2          #+#    #+#             */
/*   Updated: 2023/11/06 19:30:47 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_ultimate_range(int **range, int min, int max)
{
	int	i;

	i = 0;
	if (min >= max)
	{
		*range = NULL;
		return (0);
	}
	else
	{
		*range = (int *) malloc((max - min) * sizeof(int));
		if (*range == NULL)
			return (-1);
		while (min + i < max)
		{
			(*range)[i] = min + i;
			i++;
		}
	}
	return (i);
}
