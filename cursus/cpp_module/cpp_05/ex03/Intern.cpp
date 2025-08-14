/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 13:28:33 by igarcia2          #+#    #+#             */
/*   Updated: 2025/08/14 13:28:39 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"

//Constructor
Intern::Intern()
{
	functions[0] = &Intern::createShrubberyForm;
	functions[1] = &Intern::createRobotomyForm;
	functions[2] = &Intern::createPresidentialForm;
}

Intern::Intern(const Intern &other)
{
	*this = other;
}

//Destructor
Intern::~Intern() {}

//Operator
Intern& Intern::operator=(const Intern &other)
{
	this->functions[0] = other.functions[0];
	this->functions[1] = other.functions[1];
	this->functions[2] = other.functions[2];
	
	return (*this);
}

AForm*	Intern::makeForm(const std::string& formName,
	const std::string& target) const
{
	int	index;

	index = (formName == "shrubberyForm") * 1
		+ (formName == "robotomyForm") * 2
		+ (formName == "presidentialForm") * 3;
	if (index == 0)
	{
		std::cerr << "Form name not recognized" << std::endl;
		return (NULL);
	}
	else
	{
		std::cout << "Intern creates " << formName << std::endl;
		return ((this->*functions[index - 1])(target));
	}
}

AForm*	Intern::createShrubberyForm(const std::string &target) const
{
	return (new ShrubberyCreationForm(target));
}

AForm*	Intern::createPresidentialForm(const std::string &target) const
{
	return (new PresidentialPardonForm(target));
}
AForm*	Intern::createRobotomyForm(const std::string &target) const
{
	return (new RobotomyRequestForm(target));
}
