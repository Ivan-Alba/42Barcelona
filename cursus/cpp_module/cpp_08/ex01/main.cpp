#include "Span.hpp"
#include <iostream>
#include <deque>

int	main()
{
	Span sp = Span(10005);
	
	std::vector<int> vec;
	std::deque<int> deq;
	
	for (int i = 1; i <= 5000; i++)
	{
		vec.push_back(i);
	}

	for (int i = 5001; i <= 10000; i++)
	{
		deq.push_back(i);
	}

	try
	{
		sp.addNumber(-50);
		sp.addNumber(-100);
		sp.addNumber(-1000);
		sp.addNumber(-2000);
		sp.addNumber(-5000);

		sp.addNumber(vec.begin(), vec.end());
		sp.addNumber(deq.begin(), deq.end());

		//sp.addNumber(42); //Provoke exception
	}
	catch (std::exception &e)
	{
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}
	
	std::cout << sp.shortestSpan() << std::endl;
	std::cout << sp.longestSpan() << std::endl;
	
	return (0);
}
