/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:38:49 by igarcia2          #+#    #+#             */
/*   Updated: 2025/04/30 17:43:20 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"
#include <iostream>

Harl::Harl()
{
	functions[0] = &Harl::debug;
	functions[1] = &Harl::info;
	functions[2] = &Harl::warning;
	functions[3] = &Harl::error;
}

void	Harl::debug(void)
{
	std::clog << "I love having extra bacon for my" <<
		" 7XL-double-cheese-triple-pickle-special-ketchup burger. I really do!"
	<< std::endl;
}

void	Harl::info(void)
{
	std::clog << "I cannot believe adding extra bacon costs more money. "
		<< "You didn’t put enough bacon in my burger! If you did, "
		<< "I wouldn’t be asking for more!"	<< std::endl;
}

void	Harl::warning(void)
{
	std::cout << "I think I deserve to have some extra bacon for free. "
		<< "I’ve been coming for years, whereas you started working here "
		<< "just last month." << std::endl;
}

void	Harl::error(void)
{
	std::cerr << "This is unacceptable! I want to speak to the manager now."
		<< std::endl;
}

void	Harl::complain(std::string level)
{
	int	index = -1;

	if (level == "DEBUG") index = 0;
	if (level == "INFO") index = 1;
	if (level == "WARNING") index = 2;
	if (level == "ERROR") index = 3;

	switch (index)
	{
		case 0:
			debug();
			//fallthrough
		
		case 1:
			info();
			//fallthrough
		case 2:
			warning();
			//fallthrough
		case 3:
			error();
			break;

		default:
			std::cout
				<< "[ Probably complaining about insignificant problems ]"
				<< std::endl;
	}
}
