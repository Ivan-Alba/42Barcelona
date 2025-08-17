#include "Array.hpp"
#include <stdexcept>

template <typename T>
Array<T>::Array()
{
	array = NULL;
	len = 0;
}

template <typename T>
Array<T>::Array(unsigned int n)
{
	array = new T[n];
	len = n;
}

template <typename T>
Array<T>::Array(const Array &other)
{
	len = other.len;
	array = new T[len];
	for (size_t i = 0; i < len; i++)
	{
		array[i] = other.array[i];
	}
}

template <typename T>
Array<T>::~Array()
{
	delete[] array;
}

template <typename T>
Array<T>& Array<T>::operator=(const Array<T> &other)
{
	if (this != &other)
	{
		delete[] array;
		len = other.len;
		array = new T[len];

		for (size_t i = 0; i < len; i++)
			this->array[i] = other.array[i];
	}

	return (*this);	
}

template <typename T>
size_t Array<T>::size() const
{
	return len;	
}

template <typename T>
T& Array<T>::operator[](size_t index)
{
	if (index >= size())
		throw std::out_of_range("Index out of bounds");
	return this->array[index];
}

template <typename T>
const T& Array<T>::operator[](size_t index) const
{
	if (index >= size())
		throw std::out_of_range("Index out of bounds");
	return this->array[index];
}
