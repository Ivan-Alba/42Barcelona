/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:42:56 by igarcia2          #+#    #+#             */
/*   Updated: 2025/04/30 17:42:58 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"
#include <iostream>

int	main(void)
{
	Harl harl;

	std::cout << "DEBUG: " << std::endl;
	harl.complain("DEBUG");
	std::cout << "INFO: " << std::endl;
	harl.complain("INFO");
	std::cout << "WARNING: " << std::endl;
	harl.complain("WARNING");
	std::cout << "ERROR: " << std::endl;
	harl.complain("ERROR");
	
	return (0);
}
