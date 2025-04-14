#include "AMateria.hpp"
#include "ICharacter.hpp"
#include <iostream>

//Constructors
AMateria::AMateria() {}

AMateria::AMateria(const AMateria &other)
{
	*this = other;
}

AMateria::AMateria(const std::string &type)
{
	this->type = type;
}

//Destructor
AMateria::~AMateria() {}

//Operator
AMateria&	AMateria::operator=(const AMateria &other)
{
	if (this != &other)
	{
		this->setType(other.getType());
	}

	return (*this);
}

//Getter/Setter
void	AMateria::setType(const std::string &type)
{
	this->type = type;
}

std::string const &	AMateria::getType() const
{
	return (this->type);
}

void	AMateria::use(ICharacter &target)
{
	std::cout << "Abstract class use method" << target.getName() << std::endl;
}
