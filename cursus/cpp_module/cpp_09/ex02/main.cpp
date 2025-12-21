#include "PmergeMe.hpp"
#include <iostream>
#include <cstdlib>
#include <sys/time.h>

long timeval_diff(const timeval &start, const timeval &end)
{
	return (end.tv_sec - start.tv_sec) * 1000000L + (end.tv_usec - start.tv_usec);
}

void	printDeq(const std::deque<unsigned int> &before,
			const std::deque<unsigned int> &after)
{
	std::cout << "Before: ";
	for (size_t i = 0; i < before.size(); ++i)
	{
		std::cout << before.at(i) << " ";
	}
	std::cout << std::endl;

	std::cout << "After: ";
	for (size_t i = 0; i < after.size(); ++i)
	{
		std::cout << after.at(i) << " ";
	}
	std::cout << std::endl;
}

std::deque<unsigned int>	sortDeq(int ac, char **av, long &time)
{
	PmergeMe 					pmm;
	std::deque<unsigned int>	deq;
	std::deque<unsigned int>	sortedDeq;
	timeval						start, end;

	gettimeofday(&start, NULL);
	for(int i = 1; i < ac; ++i)
	{
		std::string str = av[i];
		deq.push_back(pmm.parseNumber(str));
	}

	pmm.mergeInsertionSort(deq, sortedDeq);

	gettimeofday(&end, NULL);
	time = timeval_diff(start, end);	

	printDeq(deq, sortedDeq);

	return (sortedDeq);
}

std::vector<unsigned int>	sortVec(int ac, char **av, long &time)
{
	PmergeMe 					pmm;
	std::vector<unsigned int>	vec;
	std::vector<unsigned int>	sortedVec;
	timeval						start, end;

	gettimeofday(&start, NULL);
	for(int i = 1; i < ac; ++i)
	{
		std::string str = av[i];
		vec.push_back(pmm.parseNumber(str));
	}

	pmm.mergeInsertionSort(vec, sortedVec);

	gettimeofday(&end, NULL);
	time = timeval_diff(start, end);

	return (sortedVec);
}

int	main(int ac, char **av)
{

	if (ac < 2)
	{
		std::cerr << "Error: invalid number of arguments" << std::endl;
		return (EXIT_FAILURE);
	}

	long	timeVec, timeDeq;
	std::deque<unsigned int> sortedDeq;
	std::vector<unsigned int> sortedVec;

	try
	{
		sortedDeq = sortDeq(ac, av, timeDeq);
		sortedVec = sortVec(ac, av, timeVec);
	}
	catch (std::invalid_argument &e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return (EXIT_FAILURE);
	}

	std::cout << "Time to process a range of " << (ac - 1)
		<< " elements with std::vector : " << timeVec << " us" << std::endl;
	
	std::cout << "Time to process a range of " << (ac - 1)
		<< " elements with std::deque : " << timeDeq << " us" << std::endl;
	
	return (EXIT_SUCCESS);
}
