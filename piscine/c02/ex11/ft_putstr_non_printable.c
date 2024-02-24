/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_non_printable.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:55:01 by igarcia2          #+#    #+#             */
/*   Updated: 2023/10/24 20:40:14 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putstr_non_printable(char *str)
{
	unsigned char	byte;
	char			hex[3];

	while (*str != '\0')
	{
		if (*str < 32 || *str >= 127)
		{
			byte = *str;
			hex[0] = '\\';
			hex[1] = "0123456789abcdef"[byte / 16];
			hex[2] = "0123456789abcdef"[byte % 16];
			write(1, hex, 3);
		}
		else
		{
			write(1, str, 1);
		}
		str++;
	}
}
