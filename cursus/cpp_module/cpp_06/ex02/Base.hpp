#ifndef BASE_HPP
#define BASE_HPP

#include <cstdlib>
#include <ctime>

class A;
class B;
class C;

class Base {

	public:
		virtual ~Base();
	
		Base*	generate();
		void	identify(Base &p);
		void	identify(Base *p);
	
};

#endif
