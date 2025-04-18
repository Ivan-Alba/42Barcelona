/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:38:09 by igarcia2          #+#    #+#             */
/*   Updated: 2025/04/18 20:01:34 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"
#include <fstream>

//Constructor
ShrubberyCreationForm::ShrubberyCreationForm()
	: AForm("shrubberyForm", 145, 137), target("defaultTarget") {}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &other)
	: AForm(other.getName(), other.getSignGrade(), other.getExecGrade()),
	target(other.target)
{
	this->setSigned(other.isSigned());
}

ShrubberyCreationForm::ShrubberyCreationForm(const std::string &target)
	: AForm("shruberryForm", 145, 137), target(target) {}

//Destructor
ShrubberyCreationForm::~ShrubberyCreationForm() {}

//Operator
ShrubberyCreationForm&
	ShrubberyCreationForm::operator=(const ShrubberyCreationForm &other)
{
	if (this != &other)
	{
		this->setSigned(other.isSigned());
	}
	return (*this);
}

//Other
void	ShrubberyCreationForm::execute(Bureaucrat const &executor) const
{
	if (!this->isSigned())
	{
		throw FormNotSignedException();
	}
	if (executor.getGrade() > this->getExecGrade())
	{
		throw GradeTooLowException();
	}

	std::ofstream	file((this->target + "_shrubbery").c_str());

    if (!file)
	{
        std::cerr << "Error creating file" << std::endl;
    }
}
