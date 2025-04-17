#include "Cure.hpp"
#include <iostream>

//Constructor
Cure::Cure()
{
	//std::cout << "Cure constructor called" << std::endl;
	setType("cure");
}

Cure::Cure(const Cure &other) : AMateria(other)
{
	*this = other;
}

//Destructor
Cure::~Cure()
{
	//std::cout << "Cure destructor called" << std::endl;
}

//Operator
Cure& Cure::operator=(const Cure &other)
{
	if (this != &other)
	{
		this->setType("cure");
	}
	return (*this);
}

//Action
void	Cure::use(ICharacter &target)
{
	std::cout << "* heals " << target.getName() << "'s wounds *" << std::endl;
}

AMateria* Cure::clone() const
{
	AMateria *clone = new Cure();

	return (clone);
}

