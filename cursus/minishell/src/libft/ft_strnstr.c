/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:23:45 by igarcia2          #+#    #+#             */
/*   Updated: 2024/09/23 16:54:44 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	res = (char *) big;
	if (ft_strlen(little) == 0)
		return (res);
	while (big[i] != '\0' && len > 0)
	{
		j = 0;
		while (big[i] == little[j])
		{
			len--;
			i++;
			j++;
			if (little[j] == '\0')
				return (&res[i - j]);
			if (len == 0)
				return (NULL);
		}
		len += j - 1;
		i -= j - 1;
	}
	return (NULL);
}
