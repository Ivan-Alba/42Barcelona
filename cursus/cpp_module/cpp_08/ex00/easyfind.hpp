#ifndef EASYFIND_HPP
#define EASYFIND_HPP

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <list>
#include <deque>
#include <algorithm>

template <typename T>
void	easyfind(const T &container, int value)
{
	std::cout << "Searching value " << value << " in container." << std::endl;

	typename T::const_iterator it = std::find(
		container.begin(), container.end(), value);
	
	if (it != container.end())
	{
		std::cout << "Value " << value << " found." << std::endl;
	}
	else
	{
		std::ostringstream oss;
		oss << "Value " << value << " not found";
		throw std::runtime_error(oss.str());
	}
}

#endif
