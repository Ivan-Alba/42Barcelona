#include "MateriaSource.hpp"
#include <iostream>

MateriaSource::MateriaSource()
{
	//std::cout << "MateriaSource default constructor called" << std::endl;
	for (int i = 0; i < 4; i++)
	{
		this->src[i] = NULL;
	}
}

MateriaSource::MateriaSource(const MateriaSource &other)
{
	//std::cout << "MateriaSource default constructor called" << std::endl;
	*this = other;
}

MateriaSource::~MateriaSource()
{
	for (int i = 0; i < 4; i++)
	{
		if (this->src[i])
		{
			delete this->src[i];
			this->src[i] = NULL;
		}
	}
}

MateriaSource& MateriaSource::operator=(const MateriaSource &other)
{
	if (this != &other)
	{
		for (int i = 0; i < 4; i++)
		{
			if (this->src[i])
				delete this->src[i];
			this->src[i] = other.src[i];
		}
	}
	
	return (*this);
}

void	MateriaSource::learnMateria(AMateria *m)
{
	for(int i = 0; i < 4; i++)
	{
		if (!this->src[i])
		{
			this->src[i] = m;
			return ;
		}
	}
}

AMateria* MateriaSource::createMateria(std::string const &type)
{
	for (int i = 0; i < 4; i++)
	{
		if (this->src[i] && this->src[i]->getType() == type)
		{
			return (this->src[i]->clone());
		}
	}
	return (NULL);
}
