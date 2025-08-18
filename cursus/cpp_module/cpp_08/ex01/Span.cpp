#include "Span.hpp"
#include <stdexcept>
#include <algorithm>

Span::Span() : maxSize(0) {}

Span::Span(unsigned int n) : maxSize(n) {}

Span::Span(const Span &other)
{
	*this = other;
}

Span::~Span() {}

Span&	Span::operator=(const Span &other)
{
	if (this != &other)
	{
		vec = other.vec;
	}
	return (*this);
}

void	Span::addNumber(int nb)
{
	if (vec.size() < maxSize)
		vec.push_back(nb);
	else
		throw std::length_error("Cannot add number: maximum capacity reached");
}

int		Span::longestSpan() const
{
	int	max;
	int	min;
	
	if (vec.size() < 2)
		throw std::runtime_error("Cannot get longest span: less than two integers");

	min = vec[0];
	max = vec[0];

	for (std::vector<int>::const_iterator iter = vec.begin();
		iter != vec.end(); ++iter)
	{
		if ((*iter) > max)
			max = (*iter);
		if ((*iter) < min)
			min = (*iter);
	}
	return (max - min);	
}

int		Span::shortestSpan()
{
	int	min;

	if (vec.size() < 2)
		throw std::runtime_error("Cannot get shortest span: less than two integers");
	std::sort(vec.begin(), vec.end());
	
	min = vec[1] - vec[0];

	for (std::vector<int>::iterator iter = vec.begin();
		iter != vec.end() - 1; ++iter)
	{
		if ((*(iter + 1)) - (*iter) < min)
		{
			min = (*(iter + 1)) - (*iter);
		}
	}

	return (min);
}
