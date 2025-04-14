#ifndef ANIMAL_HPP
# define ANIMAL_HPP

# include <string>

class Animal
{
	protected:
		std::string type;
	
	public:
		Animal();
		Animal(const Animal &other);
		virtual ~Animal();

		Animal& operator=(const Animal &other);

		void		setType(const std::string &type);
		std::string	getType() const;

		virtual void makeSound() const = 0;
};

#endif
