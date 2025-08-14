/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 13:16:03 by igarcia2          #+#    #+#             */
/*   Updated: 2025/08/14 13:16:17 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

int	main(void)
{
	try
	{
		Bureaucrat a("Carolina", 150);
		Bureaucrat b("Jaume", 1);
		//Bureaucrat c("Ivan", 0);
		//Bureaucrat d("Ana", 151);

		//a.decrementGrade();
		//b.incrementGrade();
		
		std::cout << a << std::endl;
		std::cout << b << std::endl;
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}

	return (0);
}
