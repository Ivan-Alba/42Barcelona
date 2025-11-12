#ifndef ITER_HPP
#define ITER_HPP

#include <iostream>
#include <cstddef>

template <typename T>
void	iter(T *ptr, const size_t len, void (*f)(T&))
{
	for (size_t i = 0; i < len; i++)
	{
		f(ptr[i]);
	}
}

template <typename T>
void	print(T& item)
{
	std::cout << item << std::endl;
}

#endif
