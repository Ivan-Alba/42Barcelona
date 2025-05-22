#include "ScavTrap.hpp"
#include <iostream>

//Constructors and destructor
ScavTrap::ScavTrap()
{
	this->setHitPoints(100);
	this->setEnergyPoints(50);
	this->setAttackDamage(20);
	std::cout << "ScavTrap default constructor called." << std::endl;
}

ScavTrap::ScavTrap(const std::string &name) : ClapTrap(name)
{
	this->setHitPoints(100);
	this->setEnergyPoints(50);
	this->setAttackDamage(20);
	std::cout << "ScavTrap name constructor called." << std::endl;
}	

ScavTrap::ScavTrap(const ScavTrap &other) : ClapTrap(other)
{
	*this = other;
}

ScavTrap::~ScavTrap()
{
	std::cout << "ScavTrap destructor called" << std::endl;
}

//Getters
int	ScavTrap::getDefaultHitPoints()
{
	return (100);
}

int	ScavTrap::getDefaultEnergyPoints()
{
	return (50);
}

int	ScavTrap::getDefaultAttackDamage()
{
	return (20);
}

//Operators
ScavTrap& ScavTrap::operator=(const ScavTrap &other)
{
	if (this != &other)
	{
		this->setName(other.getName());
		this->setHitPoints(other.getHitPoints());
		this->setEnergyPoints(other.getEnergyPoints());
		this->setAttackDamage(other.getAttackDamage());
	}
	return (*this);
}

//Actions
void	ScavTrap::attack(const std::string &target)
{
	if (this->getHitPoints() == 0)
	{
		std::cout << "ScavTrap " << this->getName()
			<< " is dead. Cannot attack." << std::endl;
	}
	else if (this->getEnergyPoints() == 0)
	{
		std::cout << "ScavTrap " << this->getName()
			<< " insufficient energy points to attack!" << std::endl;
	}
	else
	{
		std::cout << "ScavTrap " << this->getName() << " attacks " << target
			<< ", causing " << this->getAttackDamage() << " points of damage!"
			<< std::endl;
		this->setEnergyPoints(this->getEnergyPoints() - 1);
	}
}

void	ScavTrap::guardGate()
{
	std::cout << "ScavTrap " << this->getName()
			<< " is now in Gate keeper mode" << std::endl;
}
