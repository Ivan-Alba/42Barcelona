#include "Array.hpp"
#include <iostream>

int	main()
{
	Array<int>* a = new Array<int>(4);
	Array<char>* b = new Array<char>(10);
	Array<std::string>* c = new Array<std::string>(6);
	Array<int>* d = new Array<int>(*a);
	
	try
	{
		std::cout << "a size: " << a->size() << std::endl;	
		for (size_t i = 0; i < a->size(); i++)
		{
			std::cout << "[" << i << "]" << (*a)[i] << std::endl;
		}

		std::cout << "b size: " << b->size() << std::endl;
		for (size_t i = 0; i < b->size(); i++)
		{
			std::cout << "[" << i << "]" << (*b)[i] << std::endl;
		}

		std::cout << "c size: " << c->size() << std::endl;
		for (size_t i = 0; i < c->size(); i++)
		{
			std::cout << "[" << i << "]" << (*c)[i] << std::endl;
		}

		//Check deep copy constructor
		std::cout << "Changed a[0] = 42" << std::endl;
		(*a)[0] = 42;
		std::cout << "d size: " << d->size() << std::endl;
		for (size_t i = 0; i < d->size(); i++)
		{
			std::cout << "[" << i << "]" << (*d)[i] << std::endl;
		}

		std::cout << "a size: " << a->size() << std::endl;	
		for (size_t i = 0; i < a->size(); i++)
		{
			std::cout << "[" << i << "]" << (*a)[i] << std::endl;
		}

		//Check deep copy operator
		(*d) = (*a);
		std::cout << "Changed b[1] = 1990" << std::endl;
		(*d)[1] = 1990;

		std::cout << "d size: " << d->size() << std::endl;
		for (size_t i = 0; i < d->size(); i++)
		{
			std::cout << "[" << i << "]" << (*d)[i] << std::endl;
		}
		
		std::cout << "a size: " << a->size() << std::endl;	
		for (size_t i = 0; i < a->size(); i++)
		{
			std::cout << "[" << i << "]" << (*a)[i] << std::endl;
		}

		//Throws exception
		std::cout << (*a)[a->size()] << std::endl;
	}
	catch (const std::out_of_range &e)
	{
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}

	delete a;
	delete b;
	delete c;
	delete d;

	return (0);
}
