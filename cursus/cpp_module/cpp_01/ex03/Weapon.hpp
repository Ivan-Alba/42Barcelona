/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:42:01 by igarcia2          #+#    #+#             */
/*   Updated: 2025/04/30 17:42:02 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef WEAPON_HPP
# define WEAPON_HPP

#include <string>

class Weapon {
private:
	std::string type;
public:
	Weapon(std::string type);

	std::string	getType() const;
	void		setType(std::string type);
};

#endif
