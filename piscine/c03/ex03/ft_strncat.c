/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:44:37 by igarcia2          #+#    #+#             */
/*   Updated: 2023/10/25 18:47:29 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

char	*ft_strncat(char *dest, char *src, unsigned int nb)
{
	int	i;

	i = 0;
	while (*dest != '\0')
	{
		dest++;
		i++;
	}
	while (*src != '\0' && nb-- > 0)
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
