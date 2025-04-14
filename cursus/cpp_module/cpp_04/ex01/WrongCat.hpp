#ifndef WRONGCAT_HPP
# define WRONGCAT_HPP

# include "WrongAnimal.hpp"
# include <string>

class WrongCat : public WrongAnimal
{	
	public:
		WrongCat();
		WrongCat(const WrongCat &other);
		~WrongCat();

		WrongCat& operator=(const WrongCat &other);

		void	makeSound();
};

#endif

