#ifndef DIAMONDTRAP_HPP
# define DIAMONDTRAP_HPP

# include "ScavTrap.hpp"
# include "FragTrap.hpp"
# include <string>

class DiamondTrap : public ScavTrap, public FragTrap
{
	private:
		std::string	name;
	public:
		DiamondTrap();
		DiamondTrap(const std::string &name);
		DiamondTrap(const DiamondTrap &other);
		~DiamondTrap();

		DiamondTrap& operator=(const DiamondTrap &other);

		std::string	getName() const;
		std::string	getClapTrapName() const;
		
		void	attack(const std::string &target);
		void	whoAmI();
};

#endif
