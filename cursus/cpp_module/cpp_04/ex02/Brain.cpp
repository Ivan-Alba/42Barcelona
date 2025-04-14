#include "Brain.hpp"
#include <iostream>

//Constructor
Brain::Brain()
{
	std::cout << "Brain default constructor called" << std::endl;
}

Brain::Brain(const Brain &other)
{
	*this = other;
	std::cout << "Brain copy constructor called" << std::endl;
}

//Destructor
Brain::~Brain()
{
	std::cout << "Brain destructor called" << std::endl;
}

//Operator
Brain& Brain::operator=(const Brain &other)
{
	if (this != &other)
	{
		for (int i = 0; i < 100; i++)
		{
			this->ideas[i] = other.ideas[i];
		}
	}

	return (*this);
}

void	Brain::setIdea(int idx, const std::string &idea)
{
	this->ideas[idx] = idea;
}

std::string	Brain::getIdea(int idx) const
{
	return (this->ideas[idx]);
}
