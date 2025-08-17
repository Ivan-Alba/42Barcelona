#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <iostream>

Base::~Base() {}

Base*	Base::generate()
{
	int option = rand() % 3;

	switch (option)
	{
		case 0:
			return new A();
		case 1:
			return new B();
		case 2:
			return new C();
		default:
			return NULL;
	}
}

void	Base::identify(Base *p)
{
	if (dynamic_cast<A*>(p))
		std::cout << "Object Type A" << std::endl;
	else if (dynamic_cast<B*>(p))
		std::cout << "Object Type B" << std::endl;
	else if (dynamic_cast<C*>(p))
		std::cout << "Object Type C" << std::endl;
	else
		std::cout << "Type not recognized" << std::endl;
}

void	Base::identify(Base &p)
{
	try
	{
		dynamic_cast<A&>(p);
		std::cout << "Object type A" << std::endl;
		return ;
	} catch(...) {}

	try
	{
		dynamic_cast<B&>(p);
		std::cout << "Object type B" << std::endl;
		return ;
	} catch(...) {}

	try
	{
		dynamic_cast<C&>(p);
		std::cout << "Object type C" << std::endl;
		return ;
	} catch(...) {}

	std::cout << "Type not recognized" << std::endl;
}
