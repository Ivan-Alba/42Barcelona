#ifndef CLAPTRAP_HPP
# define CLAPTRAP_HPP

# include <string>

class ClapTrap {

	private:
		std::string	name;
		int			hitPoints;
		int			energyPoints;
		int			attackDamage;

	public:
		ClapTrap();
		ClapTrap(const std::string name);
		ClapTrap(const ClapTrap &other);
		~ClapTrap();
		ClapTrap& operator=(const ClapTrap &other);

		void		attack(const std::string &target);
		void		takeDamage(unsigned int amount);
		void		beRepaired(unsigned int amount);

		void		setName(const std::string name);
		std::string	getName() const;
		void		setHitPoints(const int hitPoints);
		int			getHitPoints() const;
		void		setEnergyPoints(const int energyPoints);
		int			getEnergyPoints() const;
		void		setAttackDamage(const int attackDamage);
		int			getAttackDamage() const;

};


#endif
