/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:44:38 by igarcia2          #+#    #+#             */
/*   Updated: 2025/04/18 20:11:51 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"

int	main(void)
{
	try
	{
		Bureaucrat a("Carolina", 150);
		Bureaucrat b("Jaume", 1);
		ShrubberyCreationForm f("Miriam");
		PresidentialPardonForm f2("Ivan");
		RobotomyRequestForm f3("Emilie");
		
		std::cout << a << std::endl;
		std::cout << b << std::endl;

		std::cout << f << std::endl;
		
		b.executeForm(f);
		b.executeForm(f2);
		b.executeForm(f3);

		b.signForm(f);
		b.signForm(f2);
		b.signForm(f3);

		b.executeForm(f);
		b.executeForm(f2);
		b.executeForm(f3);

		a.executeForm(f);
		a.executeForm(f2);
		a.executeForm(f3);

	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}

	return (0);
}
