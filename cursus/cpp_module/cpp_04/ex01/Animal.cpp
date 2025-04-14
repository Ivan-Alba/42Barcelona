#include "Animal.hpp"
#include <iostream>

Animal::Animal()
{
	std::cout << "Animal default constructor called" << std::endl;
}

Animal::Animal(const Animal &other)
{
	std::cout << "Animal copy constructor called" << std::endl;
	*this = other;
}

Animal::~Animal()
{
	std::cout << "Animal destructor called" << std::endl;
}

Animal& Animal::operator=(const Animal &other)
{
	if (this != &other)
	{
		this->setType(other.getType());
	}
	return (*this);
}

void	Animal::setType(const std::string &type)
{
	this->type = type;
}

std::string	Animal::getType() const
{
	return (this->type);
}

void	Animal::makeSound()
{
	std::cout << "..." << std::endl;
}
