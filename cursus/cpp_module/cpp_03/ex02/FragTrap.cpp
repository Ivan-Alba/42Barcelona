#include "FragTrap.hpp"
#include <iostream>

//Constructors and destructor
FragTrap::FragTrap()
{
	this->setHitPoints(100);
	this->setEnergyPoints(100);
	this->setAttackDamage(30);
	std::cout << "FragTrap default constructor called." << std::endl;
}

FragTrap::FragTrap(const std::string &name) : ClapTrap(name)
{
	this->setHitPoints(100);
	this->setEnergyPoints(100);
	this->setAttackDamage(30);
	std::cout << "FragTrap name constructor called." << std::endl;
}	

FragTrap::FragTrap(const FragTrap &other) : ClapTrap(other)
{
	*this = other;
}

FragTrap::~FragTrap()
{
	std::cout << "FragTrap destructor called" << std::endl;
}

//Operators
FragTrap& FragTrap::operator=(const FragTrap &other)
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
void	FragTrap::attack(const std::string &target)
{
	if (this->getHitPoints() == 0)
	{
		std::cout << "FragTrap " << this->getName()
			<< " is dead. Cannot attack." << std::endl;
	}
	else if (this->getEnergyPoints() == 0)
	{
		std::cout << "FragTrap " << this->getName()
			<< " insufficient energy points to attack!" << std::endl;
	}
	else
	{
		std::cout << "FragTrap " << this->getName() << " attacks " << target
			<< ", causing " << this->getAttackDamage() << " points of damage!"
			<< std::endl;
		this->setEnergyPoints(this->getEnergyPoints() - 1);
	}
}

void	FragTrap::highFivesGuys()
{
	std::cout << "FragTrap " << this->getName()
			<< " high fives guys!" << std::endl;
}
