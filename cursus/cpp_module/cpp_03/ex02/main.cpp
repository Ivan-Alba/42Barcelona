#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"
#include <iostream>

int	main(void)
{
	ClapTrap c("Harl");
	ScavTrap s("Scav");
	FragTrap f("Frag");
	FragTrap f2;

	c.attack("Carlos");
	std::cout << "HP: " << c.getHitPoints() << std::endl;
	std::cout << "EP: " << c.getEnergyPoints() << std::endl;
	s.attack("Harl");
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
	std::cout << "Scav HP: " << s.getHitPoints() << std::endl;
	std::cout << "Scav EP: " << s.getEnergyPoints() << std::endl;
	s.guardGate();
	f.highFivesGuys();
	return (0);
}
