#include "DiamondTrap.hpp"
#include <iostream>

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

DiamondTrap::~DiamondTrap()
{
	std::cout << "DiamondTrap destructor called" << std::endl;
}

void	DiamondTrap::attack(const std::string& target)
{
	ScavTrap::attack(target);
}

void	DiamondTrap::whoAmI()
{
	std::cout << "I am " << this->name << " from "
		<< ClapTrap::getName() << std::endl;
}
