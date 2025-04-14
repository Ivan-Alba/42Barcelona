#ifndef DOG_HPP
# define DOG_HPP

# include "Animal.hpp"
# include "Brain.hpp"
# include <string>

class Dog : public Animal
{
	private:
		Brain* brain;

	public:
		Dog();
		Dog(const Dog &other);
		~Dog();

		Dog& operator=(const Dog &other);

		void	makeSound();

		void	setBrain(const Brain *brain);
		Brain*	getBrain() const;
};

#endif
