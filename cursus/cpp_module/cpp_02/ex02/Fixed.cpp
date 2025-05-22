#include "Fixed.hpp"
#include <iostream>
#include <cmath>

Fixed::Fixed()
{
	this->number = 0;
}

Fixed::Fixed(const int value)
{
	this->number = value * (1 << this->fractional);
}

Fixed::Fixed(const float value)
{
	this->number = roundf(value * (1 << this->fractional));
}

Fixed::Fixed(const Fixed &other)
{
	*this = other;
}

Fixed& Fixed::operator=(const Fixed& other)
{
	if (this != &other)
		this->number = other.getRawBits();
	return (*this);
}

const Fixed& Fixed::min(const Fixed& f1, const Fixed& f2)
{
	if (f1.getRawBits() > f2.getRawBits())
		return (f2);
	return (f1);
}

const Fixed& Fixed::max(const Fixed& f1, const Fixed& f2)
{
	if (f1.getRawBits() < f2.getRawBits())
		return (f2);
	return (f1);
}

Fixed& Fixed::min(Fixed& f1, Fixed& f2)
{
	if (f1.getRawBits() > f2.getRawBits())
		return (f2);
	return (f1);
}

Fixed& Fixed::max(Fixed& f1, Fixed& f2)
{
	if (f1.getRawBits() < f2.getRawBits())
		return (f2);
	return (f1);
}

bool Fixed::operator<(const Fixed& other) const
{
	if (this->getRawBits() < other.getRawBits())
		return (true);
	return (false);
}

bool Fixed::operator>(const Fixed& other) const
{
	if (this->getRawBits() > other.getRawBits())
		return (true);
	return (false);
}

bool Fixed::operator<=(const Fixed& other) const
{
	if (this->getRawBits() <= other.getRawBits())
		return (true);
	return (false);
}

bool Fixed::operator>=(const Fixed& other) const
{
	if (this->getRawBits() >= other.getRawBits())
		return (true);
	return (false);
}

bool Fixed::operator==(const Fixed& other) const
{
	if (this->getRawBits() == other.getRawBits())
		return (true);
	return (false);
}

bool Fixed::operator!=(const Fixed& other) const
{
	if (this->getRawBits() != other.getRawBits())
		return (true);
	return (false);
}

Fixed	Fixed::operator+(const Fixed &other) const
{
	return (Fixed(this->toFloat() + other.toFloat()));
}

Fixed	Fixed::operator-(const Fixed &other) const
{
	return (Fixed(this->toFloat() - other.toFloat()));
}

Fixed	Fixed::operator*(const Fixed &other) const
{
	return (Fixed(this->toFloat() * other.toFloat()));
}

Fixed	Fixed::operator/(const Fixed &other) const
{
	return (Fixed(this->toFloat() / other.toFloat()));
}

Fixed&	Fixed::operator++()
{
	this->number++;
	return (*this);
}

Fixed	Fixed::operator++(int)
{
	Fixed temp = *this;
	this->number++;
	return (temp);
}

Fixed&	Fixed::operator--()
{
	this->number--;
	return (*this);
}

Fixed	Fixed::operator--(int)
{
	Fixed temp = *this;
	this->number--;
	return (temp);
}

std::ostream& operator<<(std::ostream& out, const Fixed& fixed)
{
	out << fixed.toFloat();
	return (out);
}

Fixed::~Fixed()
{
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
	if (this->number >= 0)
		return (this->number >> this->fractional); 
	else
		return -((-this->number) >> this->fractional);
}
