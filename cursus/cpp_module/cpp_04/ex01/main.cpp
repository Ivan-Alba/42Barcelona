#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

#include <iostream>

int	main()
{
	const Animal* j = new Dog();
	const Animal* i = new Cat();
	Dog	*d = new Dog();
	Dog h;

	h = *d;
	
	delete (j); //should not create a leak
	delete (i);
	delete (d);

	return (0);
}
