#include "Dog.hpp"
#include <iostream>

Dog::Dog()
{
	setType("Dog");
	std::cout << "Dog default constructor called" << std::endl;
}

Dog::Dog(const Dog &other) : Animal()
{
	std::cout << "Dog copy constructor called" << std::endl;
	*this = other;
}

Dog::~Dog()
{
	std::cout << "Dog destructor called" << std::endl;
}

Dog& Dog::operator=(const Dog &other)
{
	if (this != &other)
	{
		this->setType(other.getType());
	}
	return (*this);
}

void	Dog::makeSound()
{
	std::cout << "Woof woof!" << std::endl; 
}
