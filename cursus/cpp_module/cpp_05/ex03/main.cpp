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
#include "Intern.hpp"

int	main(void)
{
	Intern	someRandomIntern;
	AForm*	form;

	form = someRandomIntern.makeForm("shrubberyForm", "Random");
	if (!form)
		std::cout << "Form not created" << std::endl;
	else
	{
		std::cout << "Form created: " << *form << std::endl;
		delete form;
	}

	form = someRandomIntern.makeForm("presidentialForm", "Random");
	if (!form)
		std::cout << "Form not created" << std::endl;
	else
	{
		std::cout << "Form created: " << *form << std::endl;
		delete form;
	}

	form = someRandomIntern.makeForm("robotomyForm", "Random");
	if (!form)
		std::cout << "Form not created" << std::endl;
	else
	{
		std::cout << "Form created: " << *form << std::endl;
		delete form;
	}

	form = someRandomIntern.makeForm("unknown", "Random");
	if (!form)
		std::cout << "Form not created" << std::endl;
	else
	{
		std::cout << "Form created: " << *form << std::endl;
		delete form;
	}

	return (0);
}
