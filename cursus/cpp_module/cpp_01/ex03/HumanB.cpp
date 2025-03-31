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
	std::cout << getName() << " attacks with their "
		<< getWeapon()->getType() << std::endl;
}
