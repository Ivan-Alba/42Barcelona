#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

# include <iostream>
# include <string>

class Zombie {
private:
    std::string name;

public:
	void	announce(void);

	static Zombie	*zombieHorde(int n, std::string name);

	std::string	getName() const;

	void	setName(std::string name);

	~Zombie(void);
};

#endif

