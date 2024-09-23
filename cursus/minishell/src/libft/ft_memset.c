/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 18:11:31 by igarcia2          #+#    #+#             */
/*   Updated: 2024/09/23 16:59:32 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memset(void *ptr, int c, size_t len)
{
	char	*tmp;

	tmp = ptr;
	while (len > 0)
	{
		*tmp = c;
		tmp++;
		len--;
	}
	return (ptr);
}
