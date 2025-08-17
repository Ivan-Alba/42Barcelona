#include "Base.hpp"

int	main()
{
	std::srand(static_cast<unsigned int>(std::time(NULL)));
	
	Base *base = new Base;

	Base *b1 = base->generate();
	Base *b2 = base->generate();
	Base *b3 = base->generate();

	base->identify(b1);
	base->identify(b2);
	base->identify(b3);

	base->identify(*b1);
	base->identify(*b2);
	base->identify(*b3);
	
	delete base;
	delete b1;
	delete b2;
	delete b3;

	return (0);
}
