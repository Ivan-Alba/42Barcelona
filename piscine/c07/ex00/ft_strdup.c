/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 19:09:31 by igarcia2          #+#    #+#             */
/*   Updated: 2023/11/06 19:43:08 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strdup(char *src)
{
	int		size;
	char	*copy;
	int		i;

	i = 0;
	size = 0;
	while (src[size] != '\0')
	{
		size++;
	}
	copy = (char *) malloc((size + 1) * sizeof(char));
	if (copy)
	{
		while (src[i] != '\0')
		{
			copy[i] = src[i];
			i++;
		}
		copy[i] = '\0';
	}
	else
		return (NULL);
	return (copy);
}
