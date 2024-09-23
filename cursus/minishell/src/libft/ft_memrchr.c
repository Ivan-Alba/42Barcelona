/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 19:17:46 by igarcia2          #+#    #+#             */
/*   Updated: 2024/09/23 16:59:20 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memrchr(const void *s, int c, size_t n)
{
	int				len;
	unsigned char	*tmp;

	tmp = (unsigned char *) s;
	len = 0;
	while (tmp[len] != '\0')
	{
		len++;
	}
	while (len >= 0 && n > 0)
	{
		if (tmp[len] == c)
			return (&tmp[len]);
		len--;
		n--;
	}
	return (NULL);
}
