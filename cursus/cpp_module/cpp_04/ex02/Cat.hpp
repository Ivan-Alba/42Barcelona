#ifndef CAT_HPP
# define CAT_HPP

# include "Animal.hpp"
# include "Brain.hpp"
# include <string>

class Cat : public Animal
{
	private:
		Brain* brain;

	public:
		Cat();
		Cat(const Cat &other);
		~Cat();

		Cat& operator=(const Cat &other);

		void	makeSound() const;
		
		void	setBrain(const Brain *brain);
		Brain*	getBrain() const;
};

#endif
