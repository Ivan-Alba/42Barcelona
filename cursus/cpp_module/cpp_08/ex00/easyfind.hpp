#ifndef EASYFIND_HPP
#define EASYFIND_HPP

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <list>
#include <deque>

template <typename T>
void	easyfind(const T &container, int value)
{
	std::cout << "Searching value " << value << " in container." << std::endl;
	for (typename T::const_iterator iter = container.begin();
		iter != container.end(); ++iter)
	{
		if (*iter == value)
		{
			std::cout << "Value " << value << " found." << std::endl;
			return ;
		}
	}

	std::ostringstream oss;
	oss << "Value " << value << " not found";
	throw std::runtime_error(oss.str());
}

#endif
