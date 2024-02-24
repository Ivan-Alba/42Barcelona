/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcapitalize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:18:19 by igarcia2          #+#    #+#             */
/*   Updated: 2023/10/25 18:17:38 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

char	*ft_strcapitalize(char *str)
{
	int	i;
	int	next_to_caps;

	next_to_caps = 1;
	i = 0;
	while (*str != '\0')
	{
		if (!next_to_caps && *str >= 'A' && *str <= 'Z')
			*str += 32;
		if (next_to_caps && *str >= 'a' && *str <= 'z')
		{
			*str -= 32;
			next_to_caps = 0;
		}
		else
			next_to_caps = 0;
		if (!(*str >= 48 && *str <= 57) && !(*str >= 65 && *str <= 90)
			&& !(*str >= 97 && *str <= 122))
			next_to_caps = 1;
		str++;
		i++;
	}
	str -= i;
	return (str);
}
