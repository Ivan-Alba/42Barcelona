#ifndef HUMANB_HPP
# define HUMANB_HPP

# include <string>
# include "Weapon.hpp"

class HumanB {
private:
	std::string	name;
	Weapon		*weapon;

public:
	HumanB(std::string name);

	std::string getName() const;
	void	setName(std::string name);
	
	Weapon	*getWeapon() const;
	void	setWeapon(Weapon &weapon);
	
	void	attack(void) const;
};

#endif
