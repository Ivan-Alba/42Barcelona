#include "Dog.hpp"
#include <iostream>

Dog::Dog()
{
	std::cout << "Dog default constructor called" << std::endl;
	setType("Dog");
	this->brain = new Brain();
}

Dog::Dog(const Dog &other) : Animal()
{
	std::cout << "Dog copy constructor called" << std::endl;
	*this = other;
}

Dog::~Dog()
{
	std::cout << "Dog destructor called" << std::endl;
	delete this->brain;
}

Dog& Dog::operator=(const Dog &other)
{
	if (this != &other)
	{
		this->setType(other.getType());
		this->setBrain(other.getBrain());
	}
	return (*this);
}

void	Dog::setBrain(const Brain *brain)
{
	if (this->brain)
		delete this->brain;
	this->brain = new Brain(*brain);
}

Brain*	Dog::getBrain() const
{
	return (this->brain);
}

void	Dog::makeSound()
{
	std::cout << "Woof woof!" << std::endl; 
}
