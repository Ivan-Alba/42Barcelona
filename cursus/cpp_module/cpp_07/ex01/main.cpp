#include "iter.hpp"
#include <iostream>

int	main()
{
    int	arr[] = {1, 2, 3, 4};
    iter(arr, 4, ::print);

	std::string sArr[] = {"hello", "world", "."};
	iter(sArr, 3, ::print);

	double dArr[] = {4.5, 9.2, 0.123, 42.42};
	iter(dArr, 4, ::print);

	return (0);
}
