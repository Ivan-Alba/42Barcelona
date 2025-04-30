/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zombieHorde.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:40:42 by igarcia2          #+#    #+#             */
/*   Updated: 2025/04/30 17:40:43 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie* Zombie::zombieHorde(int n, std::string name)
{
	Zombie *horde;

	if (n <= 0)
		return NULL;

	horde = new Zombie[n];
	for(int i = 0; i < n; i++)
	{
		horde[i].setName(name);
	}

	return (horde);
}
