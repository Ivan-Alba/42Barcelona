#include "DiamondTrap.hpp"
#include <iostream>

//Constructors
DiamondTrap::DiamondTrap() : ClapTrap(), ScavTrap(), FragTrap()
{
	std::cout << "DiamondTrap default constructor called" << std::endl;
	this->setHitPoints(FragTrap::getDefaultHitPoints());
	this->setEnergyPoints(ScavTrap::getDefaultEnergyPoints());
	this->setAttackDamage(FragTrap::getDefaultAttackDamage());
}

DiamondTrap::DiamondTrap(const std::string &name)
	: ClapTrap(name + "_clap_name"), ScavTrap(name), FragTrap(name), name(name)
{
	std::cout << "DiamondTrap name constructor called" << std::endl;
	this->setHitPoints(FragTrap::getDefaultHitPoints());
	this->setEnergyPoints(ScavTrap::getDefaultEnergyPoints());
	this->setAttackDamage(FragTrap::getDefaultAttackDamage());
}

//Destructor
DiamondTrap::~DiamondTrap()
{
	std::cout << "DiamondTrap destructor called" << std::endl;
}

//Operators
DiamondTrap& DiamondTrap::operator=(const DiamondTrap &other)
{
	if (this != &other)
	{
		this->name = other.getName();
		this->setName(other.getClapTrapName());
		this->setHitPoints(other.getHitPoints());
		this->setEnergyPoints(other.getEnergyPoints());
		this->setAttackDamage(other.getAttackDamage());
	}
	return (*this);
}

//Getters
std::string	DiamondTrap::getName() const
{
	return this->name;
}

std::string	DiamondTrap::getClapTrapName() const
{
	return ClapTrap::getName();
}

//Actions
void	DiamondTrap::attack(const std::string& target)
{
	ScavTrap::attack(target);
}

void	DiamondTrap::whoAmI()
{
	std::cout << "I am " << this->name << " from "
		<< ClapTrap::getName() << std::endl;
}
