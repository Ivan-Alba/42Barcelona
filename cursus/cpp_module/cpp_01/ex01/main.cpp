/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:40:18 by igarcia2          #+#    #+#             */
/*   Updated: 2025/04/30 17:40:19 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int	main(void)
{
	Zombie	*horde;
	int		n;

	n = 8;
	if (n <= 0)
		return (0);
	horde = Zombie::zombieHorde(n, "Wilfred");
	for (int i = 0; i < n; i++)
	{
		horde[i].announce();
	}
	delete[] horde;

	return(0);
}
