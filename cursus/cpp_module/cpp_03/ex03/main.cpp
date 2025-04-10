#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"
#include "DiamondTrap.hpp"
#include <iostream>

int	main(void)
{
	ClapTrap c("Harl");
	ScavTrap s("Scav");
	FragTrap f("Frag");
	DiamondTrap d("Ellon");

	c.attack("Carlos");
	s.attack("Harl");
	c.beRepaired(10);
	c.takeDamage(9);
	c.attack("Josefo");
	c.takeDamage(20);
	c.attack("Nadie");
	s.guardGate();
	f.highFivesGuys();
	d.whoAmI();
	d.attack("Harl");
	std::cout << d.getName() << ": " << d.getHitPoints() << ", "
		<< d.getEnergyPoints() << ", " << d.getAttackDamage() << std::endl;
	return (0);
}
