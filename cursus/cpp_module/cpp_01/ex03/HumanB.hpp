/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:41:47 by igarcia2          #+#    #+#             */
/*   Updated: 2025/04/30 17:41:48 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
