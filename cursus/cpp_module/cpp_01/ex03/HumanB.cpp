/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:41:45 by igarcia2          #+#    #+#             */
/*   Updated: 2025/05/07 16:38:41 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanB.hpp"
#include <iostream>

HumanB::HumanB(std::string name) : name(name), weapon(NULL) {}

std::string	HumanB::getName() const
{
	return (name);
}

Weapon*	HumanB::getWeapon() const
{
	return (weapon);
}

void	HumanB::setName(std::string name)
{
	this->name = name;
}

void	HumanB::setWeapon(Weapon &weapon)
{
	this->weapon = &weapon;
}

void	HumanB::attack() const
{
	if (this->getWeapon())
	{
		std::cout << getName() << " attacks with their "
			<< getWeapon()->getType() << std::endl;
	}
	else
	{
		std::cout << getName() << " attacks without weapons" << std::endl;
	}
}
