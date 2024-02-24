/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 16:58:26 by igarcia2          #+#    #+#             */
/*   Updated: 2023/11/04 11:01:50 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_sqrt(int nb)
{
	long	right;
	long	left;
	long	index;

	if (nb < 0)
		return (0);
	if (nb == 1)
		return (1);
	left = 0;
	right = nb;
	while (right - left > 1)
	{
		index = (right + left) / 2;
		if (index * index == nb)
			return (index);
		else if (index * index > nb)
			right = index;
		else
			left = index;
	}
	return (0);
}
