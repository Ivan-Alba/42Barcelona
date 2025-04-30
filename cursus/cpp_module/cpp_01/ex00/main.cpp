/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:39:39 by igarcia2          #+#    #+#             */
/*   Updated: 2025/04/30 17:39:41 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int	main(void)
{
	Zombie	*newZombie;

	Zombie::randomChump("Wilfred");
	newZombie = Zombie::newZombie("Alfred");
	newZombie->Zombie::announce();

	delete newZombie;

	return(0);
}
