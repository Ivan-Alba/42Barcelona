#include "Ice.hpp"
#include <iostream>

//Constructor
Ice::Ice()
{
	//std::cout << "Ice constructor called" << std::endl;
	setType("ice");
}

Ice::Ice(const Ice &other) : AMateria(other)
{
	*this = other;
}

//Destructor
Ice::~Ice()
{
	//std::cout << "Ice destructor called" << std::endl;
}


//Operator
Ice& Ice::operator=(const Ice &other)
{
	if (this != &other)
	{
		this->setType("ice");
	}
	return (*this);
}

//Action
void	Ice::use(ICharacter &target)
{
	std::cout << "* shoots an ice bolt at " << target.getName() << " *"
		<< std::endl;
}

AMateria* Ice::clone() const
{
	AMateria *clone = new Ice();

	return (clone);
}
