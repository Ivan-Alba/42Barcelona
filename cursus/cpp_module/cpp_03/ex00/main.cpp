#include "ClapTrap.hpp"
#include <iostream>

int	main(void)
{
	ClapTrap c("Harl");

	c.attack("Carlos");
	std::cout << "HP: " << c.getHitPoints() << std::endl;
	std::cout << "EP: " << c.getEnergyPoints() << std::endl;
	c.beRepaired(10);
	std::cout << "HP: " << c.getHitPoints() << std::endl;
	std::cout << "EP: " << c.getEnergyPoints() << std::endl;
	c.takeDamage(9);
	std::cout << "HP: " << c.getHitPoints() << std::endl;
	std::cout << "EP: " << c.getEnergyPoints() << std::endl;
	c.attack("Josefo");
	std::cout << "HP: " << c.getHitPoints() << std::endl;
	std::cout << "EP: " << c.getEnergyPoints() << std::endl;
	c.takeDamage(20);
	std::cout << "HP: " << c.getHitPoints() << std::endl;
	std::cout << "EP: " << c.getEnergyPoints() << std::endl;
	c.attack("Nadie");
	std::cout << "HP: " << c.getHitPoints() << std::endl;
	std::cout << "EP: " << c.getEnergyPoints() << std::endl;
	return (0);
}
