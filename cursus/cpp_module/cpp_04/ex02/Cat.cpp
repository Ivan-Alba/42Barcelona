#include "Cat.hpp"
#include <iostream>

Cat::Cat()
{
	std::cout << "Cat default constructor called" << std::endl;
	setType("Cat");
	this->brain = new Brain();
}

Cat::Cat(const Cat &other) : Animal()
{
	std::cout << "Cat copy constructor called" << std::endl;
	*this = other;
}

Cat::~Cat()
{
	std::cout << "Cat destructor called" << std::endl;
	delete this->brain;
}

Cat& Cat::operator=(const Cat &other)
{
	if (this != &other)
	{
		this->setType(other.getType());
		this->setBrain(other.getBrain());
	}
	return (*this);
}

void	Cat::setBrain(const Brain *brain)
{
	if (this->brain)
		delete this->brain;
	this->brain = new Brain(*brain);
}

Brain*	Cat::getBrain() const
{
	return (this->brain);
}

void	Cat::makeSound() const
{
	std::cout << "meooooooooooooooow" << std::endl;
}
