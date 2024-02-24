/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:28:49 by igarcia2          #+#    #+#             */
/*   Updated: 2023/10/25 18:35:56 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned char	c1;
	unsigned char	c2;
	unsigned int	i;

	i = 0;
	while (*s1 != '0' && *s2 != '0' && i++ < n)
	{
		c1 = *s1;
		c2 = *s2;
		if (*s1 != *s2)
			return (c1 - c2);
		s1++;
		s2++;
	}
	return (0);
}
