#include "Character.hpp"
#include "AMateria.hpp"
#include <iostream>

//Constructor
Character::Character()
{
	//std::cout << "Character default constructor called" << std::endl;
	for (int i = 0; i < 4; i++)
	{
		this->inventory[i] = NULL;
	}

	for (int i = 0; i < 100; i++)
	{
		this->unequippedMateria[i] = NULL;
	}

	this->name = "";
}

Character::Character(const std::string &name)
{
	//std::cout << "Character name constructor called" << std::endl;
	for (int i = 0; i < 4; i++)
	{
		this->inventory[i] = NULL;
	}

	for (int i = 0; i < 100; i++)
	{
		this->unequippedMateria[i] = NULL;
	}

	this->name = name;
}

Character::Character(const Character &other)
{
	//std::cout << "Character copy constructor called" << std::endl;
	*this = other;
}

//Destructor
Character::~Character()
{
	//std::cout << "Character destructor called" << std::endl;
	for (int i = 0; i < 4; i++)
	{
		if (this->inventory[i])
		{
			delete (this->inventory[i]);
			this->inventory[i] = NULL;
		}
	}

	for (int i = 0; i < 100; i++)
	{
		if (this->unequippedMateria[i])
			delete this->unequippedMateria[i];
	}
}

//Operator
Character& Character::operator=(const Character &other)
{
	if (this != &other)
	{
		for (int i = 0; i < 4; i++)
		{
			if (this->inventory[i])
				delete this->inventory[i];
			this->inventory[i] = other.inventory[i]->clone();
		}
		
		for (int i = 0; i < 100; i++)
		{
			if (this->unequippedMateria[i])
				delete this->unequippedMateria[i];
			this->unequippedMateria[i] = other.unequippedMateria[i]->clone();
		}
	}
	
	return (*this);
}

//Getter
std::string const	&Character::getName() const
{
	return (this->name);
}

void	Character::equip(AMateria *m)
{
	if (!m)
		return;

	for (int i = 0; i < 4; i++)
	{
		if (!this->inventory[i])
		{
			this->inventory[i] = m;
			std::cout << m->getType() << " materia added to " << this->getName()
				<< "'s inventory" << std::endl;
			return ;
		}
	}
	std::cout << this->getName() << "'s inventory is full" << std::endl;
}

void	Character::unequip(int idx)
{
	if (idx < 0 || idx > 3)
	{
		std::cerr << "Error->Invalid index" << std::endl;
		return ;
	}

	for (int i = 0; i < 100; i++)
	{
		if (!this->unequippedMateria[i])
		{
			this->unequippedMateria[i] = this->inventory[idx];
			break ;
		}
	}
	this->inventory[idx] = NULL;
	std::cout << "Materia at slot[" << idx << "] unequipped" << std::endl;
}

void	Character::use(int idx, ICharacter &target)
{
	if (idx < 0 || idx > 3)
	{
		std::cerr << "Error->Invalid index" << std::endl;
		return ;
	}

	if (this->inventory[idx])
	{
		std::cout << this->getName() << ": "; 
		this->inventory[idx]->use(target);
	}
	else
	{
		std::cout << this->getName() << ": No materia setted at slot["
			<< idx << "]" << std::endl;
	}
}
