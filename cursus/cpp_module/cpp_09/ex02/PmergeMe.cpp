#include "PmergeMe.hpp"
#include <sstream>

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &other)
{
	*this = other;
}

PmergeMe::~PmergeMe() {}

PmergeMe&	PmergeMe::operator=(const PmergeMe &other)
{
	if (this != &other)
	{
	}
	return (*this);
}

void	PmergeMe::mergeInsertionSort(const std::deque<unsigned int> &input,
			std::deque<unsigned int> &sorted) const
{
	std::deque<unsigned int> losers;
	std::deque<unsigned int> winners;

	if (input.size() == 1)
	{
		sorted.push_back(input.at(0));
		return ;
	}

	for (size_t i = 0; i < input.size(); i += 2)
	{
		if (input.size() % 2 == 1 && i == input.size() - 1)
			losers.push_back(input.at(i));
		else
		{
			if (input.at(i) > input.at(i + 1))
			{
				winners.push_back(input.at(i));
				losers.push_back(input.at(i + 1));
			}
			else
			{
				losers.push_back(input.at(i));
				winners.push_back(input.at(i + 1));
			}
		}
	}
	mergeInsertionSort(winners, sorted);

	for (size_t i = 0; i < losers.size(); ++i)
	{
		std::deque<unsigned int>::iterator pos =
			std::lower_bound(sorted.begin(), sorted.end(), losers.at(i));
		sorted.insert(pos, losers.at(i));
	}
}

void	PmergeMe::mergeInsertionSort(const std::vector<unsigned int> &input,
			std::vector<unsigned int> &sorted) const
{
	std::vector<unsigned int> losers;
	std::vector<unsigned int> winners;

	if (input.size() == 1)
	{
		sorted.push_back(input.at(0));
		return ;
	}

	for (size_t i = 0; i < input.size(); i += 2)
	{
		if (input.size() % 2 == 1 && i == input.size() - 1)
			losers.push_back(input.at(i));
		else
		{
			if (input.at(i) > input.at(i + 1))
			{
				winners.push_back(input.at(i));
				losers.push_back(input.at(i + 1));
			}
			else
			{
				losers.push_back(input.at(i));
				winners.push_back(input.at(i + 1));
			}
		}
	}
	mergeInsertionSort(winners, sorted);

	for (size_t i = 0; i < losers.size(); ++i)
	{
		std::vector<unsigned int>::iterator pos =
			std::lower_bound(sorted.begin(), sorted.end(), losers.at(i));
		sorted.insert(pos, losers.at(i));
	}
}

unsigned int	PmergeMe::parseNumber(const std::string &str) const
{
	int				temp;
	unsigned int	val;

	std::stringstream ss(str);
	ss >> temp;

	if (ss.fail() || !ss.eof() || temp < 0)
	{
		throw std::invalid_argument("wrong argument format.");
	}

	val = static_cast<unsigned int>(temp);
	return (val);
}
