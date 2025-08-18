#include "Span.hpp"
#include <iostream>

int	main()
{
	std::vector<int> vec(50000);
	Span sp = Span(50005);
	
	try
	{
		sp.addNumber(-6);
		sp.addNumber(3);
		sp.addNumber(17);
		sp.addNumber(9);
		sp.addNumber(11);
		//sp.addNumber(42); //Provoke exception

		sp.addNumber(vec.begin(), vec.end());
	}
	catch (std::exception &e)
	{
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}
	
	std::cout << sp.shortestSpan() << std::endl;
	std::cout << sp.longestSpan() << std::endl;
	
	return (0);
}
