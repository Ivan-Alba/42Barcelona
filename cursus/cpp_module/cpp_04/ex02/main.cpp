#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

#include <iostream>

int	main()
{
	//Animal a;

	Dog *d = new Dog();
	Cat *c = new Cat();

	delete d;
	delete c;

	return (0);
}
