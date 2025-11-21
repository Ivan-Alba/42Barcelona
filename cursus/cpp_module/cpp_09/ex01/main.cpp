#include "RPN.hpp"
#include <iostream>
#include <cstdlib>

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cerr << "Error: invalid number of argument." << std::endl;
		return (EXIT_FAILURE);
	}

	RPN				rpn;
	std::string		line = av[1];
	unsigned int	result;

	if (!rpn.isFormatValid(line))
	{
		std::cerr << "Error: wrong format." << std::endl;
		return (EXIT_FAILURE);
	}

	try
	{
		result = rpn.calculate(line);
		std::cout << result << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return (EXIT_FAILURE);
	}

	return (EXIT_SUCCESS);
}
