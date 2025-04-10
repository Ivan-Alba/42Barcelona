#include "ClapTrap.hpp"
#include <iostream>

//Constructors
ClapTrap::ClapTrap() : hitPoints(10), energyPoints(10), attackDamage(0)
{
	std::cout << "ClapTrap default constructor called" << std::endl;
}

ClapTrap::ClapTrap(const std::string &name)
	: hitPoints(10), energyPoints(10), attackDamage(0)
{
	std::cout << "ClapTrap name constructor called" << std::endl;
	this->name = name;
}

ClapTrap::ClapTrap(const ClapTrap &other)
{
	std::cout << "ClapTrap copy constructor called" << std::endl;
	*this = other;
}

//Destructor
ClapTrap::~ClapTrap()
{
	std::cout << "ClapTrap destructor called" << std::endl;
}

//Getter & setter

void	ClapTrap::setName(const std::string name)
{
	this->name = name;
}

std::string	ClapTrap::getName() const
{
	return (this->name);
}

void	ClapTrap::setHitPoints(const int hitPoints)
{
	this->hitPoints = hitPoints;
}

int	ClapTrap::getHitPoints() const
{
	return (this->hitPoints);
}

void	ClapTrap::setEnergyPoints(const int energyPoints)
{
	this->energyPoints = energyPoints;
}

int	ClapTrap::getEnergyPoints() const
{
	return (this->energyPoints);
}

void	ClapTrap::setAttackDamage(const int attackDamage)
{
	this->attackDamage = attackDamage;
}

int	ClapTrap::getAttackDamage() const
{
	return (this->attackDamage);
}

//Operators
ClapTrap& ClapTrap::operator=(const ClapTrap &other)
{
	if (this != &other)
	{
		this->name = other.getName();
		this->hitPoints = other.getHitPoints();
		this->energyPoints = other.getEnergyPoints();
		this->attackDamage = other.getAttackDamage();
	}
	return (*this);
}

//Actions
void	ClapTrap::attack(const std::string &target)
{
	if (this->getHitPoints() == 0)
	{
		std::cout << "ClapTrap " << this->getName()
			<< " is dead. Cannot attack." << std::endl;
	}
	else if (this->getEnergyPoints() == 0)
	{
		std::cout << "ClapTrap " << this->getName()
			<< " insufficient energy points to attack!" << std::endl;

	}
	else
	{
		std::cout << "ClapTrap " << this->getName() << " attacks " << target
			<< ", causing " << this->getAttackDamage() << " points of damage!"
			<< std::endl;
		this->setEnergyPoints(this->getEnergyPoints() - 1);
	}
}

void	ClapTrap::takeDamage(unsigned int amount)
{
	if (this->getHitPoints() == 0)
	{
		std::cout << "ClapTrap " << this->getName()
			<< " is dead. Cannot take damage." << std::endl;
	}
	else
	{
		std::cout << "ClapTrap " << this->getName() << " takes " << amount
			<< " points of damage!" << std::endl;
		this->setHitPoints(this->getHitPoints() - amount);
		if (this->getHitPoints() < 0)
			this->setHitPoints(0);
	}
}

void	ClapTrap::beRepaired(unsigned int amount)
{
	if (this->getHitPoints() == 0)
	{
		std::cout << "ClapTrap " << this->getName()
			<< " is dead. Cannot repair itself." << std::endl;
	}
	else if (this->getEnergyPoints() == 0)
	{
		std::cout << "ClapTrap " << this->getName()
			<< " insufficient energy points to repair!" << std::endl;

	}
	else
	{
		std::cout << "ClapTrap " << this->getName() << " repairs itself " 					<< amount << " hit points!" << std::endl;
		this->setHitPoints(this->getHitPoints() + amount);
		this->setEnergyPoints(this->getEnergyPoints() - 1);
	}}
