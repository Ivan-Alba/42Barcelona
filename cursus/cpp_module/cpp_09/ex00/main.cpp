#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>

int	main(int ac, char **av)
{
	if (ac > 2)
	{
		std::cerr << "Error: only one arg required." << std::endl;
		return (1);
	}
	else if (ac != 2)
	{
		std::cerr << "Error: could not open file." << std::endl;
		return (1);
	}
	
	std::ifstream file(av[1]);
	if (!file.is_open())
	{
		std::cerr << "Error: could not open file." << std::endl;
		return (1);
	}

	BitcoinExchange be;
	std::string line;

	std::getline(file, line);

	while (std::getline(file, line))
	{
		be.getValue(line);
	}

	file.close();

	return (0);
}
