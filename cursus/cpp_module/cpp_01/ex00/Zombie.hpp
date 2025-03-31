#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

# include <string>

class Zombie {
private:
    std::string name;

public:
	void	announce(void);

	static Zombie	*newZombie(std::string name);

	static void	randomChump(std::string name);

	std::string	getName() const;

	void	setName(std::string name);

	~Zombie(void);
};

#endif

