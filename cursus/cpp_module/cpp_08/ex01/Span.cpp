#include "Span.hpp"
#include <stdexcept>
#include <algorithm>
#include <numeric>

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
	if (vec.size() < 2)
		throw std::runtime_error("Cannot get longest span: less than two integers");

	int	minVal = *std::min_element(vec.begin(), vec.end());
	int	maxVal = *std::max_element(vec.begin(), vec.end());
	
	return (maxVal - minVal);	
}

int		Span::shortestSpan() const
{
	if (vec.size() < 2)
		throw std::runtime_error("Cannot get shortest span: less than two integers");

	std::vector<int>	tmp(vec);
	std::vector<int>	diffs(tmp.size());
	
	std::sort(tmp.begin(), tmp.end());
	std::adjacent_difference(tmp.begin(), tmp.end(), diffs.begin());

	return (*std::min_element(diffs.begin() + 1, diffs.end()));
}
