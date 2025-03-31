#include "Zombie.hpp"

int	main(void)
{
	Zombie	*horde;
	int	n;

	n = 8;
	if (n <= 0)
		return (0);
	horde = Zombie::zombieHorde(n, "Wilfred");
	for (int i = 0; i < n; i++)
	{
		horde[i].announce();
	}
	delete[] horde;

	return(0);
}
