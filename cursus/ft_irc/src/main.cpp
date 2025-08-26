#include "Server.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

bool	parsePort(const std::string &str, int &port)
{
	std::stringstream	ss(str);
	long				val;

	if (!(ss >> val) || !(ss.eof()))
		return (false);
	if (val < 1 || val > 65535)
		return (false);

	port = static_cast<int>(val);

	return (true);
}

int	main(int ac, char **av)
{
	if (ac != 3)
	{
		std::cerr << "Error: wrong number of arguments." << std::endl;
		return (1);
	}

	std::string	portStr = av[1];
	std::string	password = av[2];
	int			port;

	if (!parsePort(portStr, port))
	{
		std::cerr << "Error: invalid port." << std::endl;
		return (EXIT_FAILURE);
	}

	try
	{
		Server server(port, password);

		server.run();

	} catch (const std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return (EXIT_FAILURE);
	}

	return (EXIT_SUCCESS);
}
