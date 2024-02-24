/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_printable.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 12:44:34 by igarcia2          #+#    #+#             */
/*   Updated: 2023/10/24 19:23:40 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_str_is_printable(char *str)
{
	int	all_printable;

	all_printable = 1;
	while (*str != '\0' && all_printable == 1)
	{
		if (*str < 32 || *str == 127)
			all_printable = 0;
		str++;
	}
	return (all_printable);
}
