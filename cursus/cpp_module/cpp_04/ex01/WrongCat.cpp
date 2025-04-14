#include "WrongCat.hpp"
#include <iostream>

WrongCat::WrongCat()
{
	setType("WrongCat");
	std::cout << "WrongCat default constructor called" << std::endl;
}

WrongCat::WrongCat(const WrongCat &other) : WrongAnimal()
{
	std::cout << "WrongCat copy constructor called" << std::endl;
	*this = other;
}

WrongCat::~WrongCat()
{
	std::cout << "WrongCat destructor called" << std::endl;
}

WrongCat& WrongCat::operator=(const WrongCat &other)
{
	if (this != &other)
	{
		this->setType(other.getType());
	}
	return (*this);
}

void	WrongCat::makeSound()
{
	std::cout << "meooooooooooooooow" << std::endl;
}
