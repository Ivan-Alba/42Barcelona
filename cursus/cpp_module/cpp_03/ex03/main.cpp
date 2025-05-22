#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"
#include "DiamondTrap.hpp"
#include <iostream>

int	main(void)
{
	DiamondTrap d("Ellon");
	DiamondTrap d2;


	d.whoAmI();
	d.attack("Harl");
	std::cout << d2.getName() << std::endl;
	d2 = d;
	std::cout << d2.getName() << std::endl;
	std::cout << d2.getClapTrapName() << std::endl;
	std::cout << d.getName() << ": " << d.getHitPoints() << ", "
		<< d.getEnergyPoints() << ", " << d.getAttackDamage() << std::endl;

	return (0);
}
