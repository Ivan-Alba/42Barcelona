/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:40:57 by igarcia2          #+#    #+#             */
/*   Updated: 2025/04/30 17:40:59 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <iostream>

int	main(void)
{
	std::string str = "HI THIS IS BRAIN";
	std::string *stringPTR = &str;
	std::string &stringREF = str;

	std::cout << "Memory address of the string: " << &str << std::endl;
	std::cout << "Memory address held by stringPTR: "
		<< stringPTR << std::endl;
	std::cout << "Memory address held by stringREF: "
		<< &stringREF << std::endl;

    std::cout << "----------------------------------" << std::endl;

	std::cout << "Value of the string: " << str << std::endl;
	std::cout << "Value pointed to by stringPTR: "
		<< *stringPTR << std::endl;
	std::cout << "Value pointed to by stringREF: "
		<< stringREF << std::endl;
	return (0);
}
