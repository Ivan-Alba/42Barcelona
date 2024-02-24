/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 10:09:30 by igarcia2          #+#    #+#             */
/*   Updated: 2023/10/24 19:21:11 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	count;
	int				dest_finish;

	dest_finish = 0;
	count = 0;
	while (count < n)
	{
		if (dest_finish == 0)
		{
			if (*src != '\0')
				*dest++ = *src;
			else
			{
				*dest++ = '\0';
				dest_finish = 1;
			}
		}
		else
			*dest++ = '\0';
		src++;
		count++;
	}
	dest -= count;
	return (dest);
}
