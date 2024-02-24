/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_lowercase.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 12:14:45 by igarcia2          #+#    #+#             */
/*   Updated: 2023/10/23 12:24:58 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_str_is_lowercase(char *str)
{
	int	all_alpha;

	all_alpha = 1;
	while (*str != '\0' && all_alpha == 1)
	{
		if (*str < 'a' || *str > 'z')
			all_alpha = 0;
		str++;
	}
	return (all_alpha);
}
