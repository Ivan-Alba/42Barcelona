/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:46:39 by igarcia2          #+#    #+#             */
/*   Updated: 2023/10/24 20:22:10 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned int	ft_strlcpy(char *dest, const char *src, unsigned int size)
{
	unsigned int	i;

	i = 0;
	if (size > 0)
	{
		while (i < (size - 1) && *src != '\0')
		{
			*dest = *src;
			src++;
			dest++;
			i++;
		}
		*dest = '\0';
	}
	while (*src != '\0')
	{
		src++;
		i++;
	}
	return (i);
}
