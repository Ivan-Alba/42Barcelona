/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_comb.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 16:59:55 by igarcia2          #+#    #+#             */
/*   Updated: 2023/10/22 10:22:07 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	write_char(char x);

void	write_number(char cen, char dec, char uni);

void	ft_print_comb(void)
{
	char	cen;
	char	dec;
	char	uni;

	cen = '0';
	while (cen <= '7')
	{
		dec = cen + 1;
		while (dec <= '8')
		{
			uni = dec + 1;
			while (uni <= '9')
			{
				write_number(cen, dec, uni);
				if (cen != '7' || dec != '8' || uni != '9')
				{
					write_char(',');
					write_char(' ');
				}
				uni++;
			}
			dec++;
		}
		cen++;
	}
}

void	write_number(char cen, char dec, char uni)
{
	write_char(cen);
	write_char(dec);
	write_char(uni);
}

void	write_char(char x)
{
	write(1, &x, 1);
}
