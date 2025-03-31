#ifndef HUMANA_HPP
# define HUMANA_HPP

# include <string>
# include "Weapon.hpp"

class HumanA {
private:
	std::string	name;
	Weapon		&weapon;

public:
	HumanA(std::string name, Weapon &weapon);
	
	std::string	getName() const;
	void		setName(std::string name);
	
	Weapon		getWeapon() const;
	void		setWeapon(Weapon &weapon);

	void		attack(void) const;
};

#endif
