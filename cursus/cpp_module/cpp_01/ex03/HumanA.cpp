#include "HumanA.hpp"
#include <iostream>

HumanA::HumanA(std::string name, Weapon &weapon) : weapon(weapon)
{
	this->name = name;
}

std::string	HumanA::getName() const
{
	return (name);
}

Weapon	HumanA::getWeapon() const
{
	return (weapon);
}

void	HumanA::setName(std::string name)
{
	this->name = name;
}

void	HumanA::setWeapon(Weapon &weapon)
{
	this->weapon = weapon;
}

void	HumanA::attack() const
{
	std::cout << getName() << " attacks with their "
		<< getWeapon().getType() << std::endl;
}
