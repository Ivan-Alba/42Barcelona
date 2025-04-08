#include "Fixed.hpp"
#include <iostream>
#include <cmath>

Fixed::Fixed()
{
	std::cout << "Default constructor called" << std::endl;
	this->number = 0;
}

Fixed::Fixed(const int value)
{
	std::cout << "Int constructor called" << std::endl;
	this->number = value * (1 << this->fractional);
}

Fixed::Fixed(const float value)
{
	std::cout << "Float constructor called" << std::endl;
	this->number = roundf(value * (1 << this->fractional));
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

std::ostream& operator<<(std::ostream& out, const Fixed& fixed)
{
	out << fixed.toFloat();
	return (out);
}

Fixed::~Fixed()
{
	std::cout << "Destructor called" << std::endl;
}

int	Fixed::getRawBits(void) const
{
	return (this->number);
}

void	Fixed::setRawBits(int const raw)
{
	this->number = raw;
}

float	Fixed::toFloat(void) const
{
	return ((float)this->number / (1 << this->fractional));
}

int	Fixed::toInt(void) const
{
	return (this->number >> this->fractional); 
}
