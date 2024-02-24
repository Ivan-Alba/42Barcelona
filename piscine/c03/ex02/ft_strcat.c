/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:37:53 by igarcia2          #+#    #+#             */
/*   Updated: 2023/10/25 18:43:26 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

char	*ft_strcat(char *dest, char *src)
{
	int	i;

	i = 0;
	while (*dest != '\0')
	{
		dest++;
		i++;
	}
	while (*src != '\0')
	{
		*dest = *src;
		src++;
		dest++;
		i++;
	}
	*dest = '\0';
	dest -= i;
	return (dest);
}
