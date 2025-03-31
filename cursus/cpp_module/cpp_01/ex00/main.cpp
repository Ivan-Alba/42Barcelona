#include "Zombie.hpp"

int	main(void)
{
	Zombie	*newZombie;

	Zombie::randomChump("Wilfred");
	newZombie = Zombie::newZombie("Alfred");
	newZombie->Zombie::announce();
	delete newZombie;
	return(0);
}
