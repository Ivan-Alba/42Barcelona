#include "Fixed.hpp"
#include <iostream>

Fixed::Fixed()
{
	std::cout << "Default constructor called" << std::endl;
	this->number = 0;
}

Fixed::Fixed(const Fixed &other)
{
	std::cout << "Copy constructor called" << std::endl;
	*this = other;
}

Fixed& Fixed::operator=(const Fixed& other)
{
	std::cout << "Copy assignment operator called" << std::endl;
	if (this != &other)
		this->number = other.getRawBits();
	return (*this);
}

Fixed::~Fixed()
{
	std::cout << "Destructor called" << std::endl;
}

int	Fixed::getRawBits(void) const
{
	std::cout << "getRawBits member function called" << std::endl;
	return (this->number);
}

void	Fixed::setRawBits(int const raw)
{
	this->number = raw;
}
