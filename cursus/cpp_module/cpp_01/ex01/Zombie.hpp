/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:40:46 by igarcia2          #+#    #+#             */
/*   Updated: 2025/04/30 17:40:47 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

# include <iostream>
# include <string>

class Zombie
{
	private:
    	std::string name;

	public:
		void	announce(void);

		static Zombie	*zombieHorde(int n, std::string name);

		std::string	getName() const;

		void	setName(std::string name);

		~Zombie(void);
};

#endif
