/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_numeric.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:07:44 by igarcia2          #+#    #+#             */
/*   Updated: 2023/10/23 12:04:36 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_str_is_numeric(char *str)
{
	int	all_alpha;

	all_alpha = 1;
	while (*str != '\0' && all_alpha == 1)
	{
		if (*str < '0' || *str > '9')
			all_alpha = 0;
		str++;
	}
	return (all_alpha);
}
