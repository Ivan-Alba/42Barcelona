#include "Zombie.hpp"

void	Zombie::randomChump(std::string name)
{
	Zombie	newZombie;

	newZombie.setName(name);
	newZombie.announce();
}
