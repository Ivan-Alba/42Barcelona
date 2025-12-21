#include "PmergeMe.hpp"
#include <sstream>
#include <algorithm>

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
		sorted.push_back(input[0]);
		return ;
	}

	size_t i = 0;
	for (i = 0; i + 1 < input.size(); i += 2)
	{
		if (input[i] > input[i + 1])
		{
			winners.push_back(input[i]);
			losers.push_back(input[i + 1]);
		}
		else
		{
			losers.push_back(input[i]);
			winners.push_back(input[i + 1]);
		}
	}

	if (i < input.size())
			losers.push_back(input[i]);

	mergeInsertionSort(winners, sorted);

	std::vector<size_t>	jacobOrder = generateJacobsthal(losers.size());
	std::vector<bool>	inserted(losers.size(), false);

	// Insert by jacobsthal order
	for (size_t i = 0; i < jacobOrder.size(); ++i)
	{
		if (jacobOrder[i] < losers.size() && !inserted[jacobOrder[i]])
		{
			std::deque<unsigned int>::iterator	pos = std::lower_bound(
				sorted.begin(), sorted.end(), losers[jacobOrder[i]]);
			sorted.insert(pos, losers[jacobOrder[i]]);
			inserted[jacobOrder[i]] = true;
		}
	}

	// Insert others
	for (size_t i = 0; i < losers.size(); ++i)
	{
		if (!inserted[i] && i < winners.size())
		{
			std::deque<unsigned int>::iterator	pos = std::lower_bound(
				sorted.begin(), std::find(
					sorted.begin(), sorted.end(), winners[i]), losers[i]);
			sorted.insert(pos, losers[i]);
		}
		else if (!inserted[i])
		{
			std::deque<unsigned int>::iterator	pos = std::lower_bound(
				sorted.begin(), sorted.end(), losers[i]);
			sorted.insert(pos, losers[i]);
		}
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

std::vector<size_t>	PmergeMe::generateJacobsthal(size_t n) const
{
	std::vector<size_t> jacobsthalSeq;
	size_t	j0 = 0; 
	size_t	j1 = 1;

	if (j1 < n) jacobsthalSeq.push_back(j1);

	while (true)
	{
		size_t j2 = j1 + 2 * j0;
		if (j2 >= n)
			break;
		jacobsthalSeq.push_back(j2);

		j0 = j1;
		j1 = j2;
	}
	
	return jacobsthalSeq;
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
