/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_uppercase.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 12:22:36 by igarcia2          #+#    #+#             */
/*   Updated: 2023/10/23 12:27:42 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_str_is_uppercase(char *str)
{
	int	all_alpha;

	all_alpha = 1;
	while (*str != '\0' && all_alpha == 1)
	{
		if (*str < 'A' || *str > 'Z')
			all_alpha = 0;
		str++;
	}
	return (all_alpha);
}
