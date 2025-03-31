#include "Zombie.hpp"

Zombie* Zombie::zombieHorde(int n, std::string name)
{
	Zombie *horde;

	if (n <= 0)
		return NULL;

	horde = new Zombie[n];
	for(int i = 0; i < n; i++)
	{
		horde[i].setName(name);
	}

	return (horde);
}
