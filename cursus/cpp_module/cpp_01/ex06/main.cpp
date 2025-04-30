/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:43:24 by igarcia2          #+#    #+#             */
/*   Updated: 2025/04/30 17:43:25 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"
#include <iostream>

int	main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cerr << "Error: ./harlFilter <level> required."
			<< std::endl;
		return (1);
	}

	Harl 		harl;
	std::string level = argv[1];

	harl.complain(level);
	
	return (0);
}
