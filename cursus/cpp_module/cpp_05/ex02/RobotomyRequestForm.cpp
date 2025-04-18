/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:42:49 by igarcia2          #+#    #+#             */
/*   Updated: 2025/04/18 20:08:55 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RobotomyRequestForm.hpp"
#include <cstdlib>
#include <ctime>

//Constructor
RobotomyRequestForm::RobotomyRequestForm()
	: AForm("robotomyForm", 72, 45), target("defaultTarget") {}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm &other)
	: AForm(other.getName(), other.getSignGrade(), other.getExecGrade()),
	target(other.target)
{
	this->setSigned(other.isSigned());
}

RobotomyRequestForm::RobotomyRequestForm(const std::string &target)
	: AForm("robotomyForm", 72, 45), target(target) {}

//Destructor
RobotomyRequestForm::~RobotomyRequestForm() {}

//Operator
RobotomyRequestForm&
	RobotomyRequestForm::operator=(const RobotomyRequestForm &other)
{
	if (this != &other)
	{
		this->setSigned(other.isSigned());
	}
	return (*this);
}

//Other
void	RobotomyRequestForm::execute(Bureaucrat const &executor) const
{
	if (!this->isSigned())
	{
		throw FormNotSignedException();
	}
	if (executor.getGrade() > this->getExecGrade())
	{
		throw GradeTooLowException();
	}
	std::cout << "BRZZZZZZZZ ";
	srand(time(0));
	if (rand() % 2 == 0)
		std::cout << this->target << " has been robotomized" << std::endl;
	else
		std::cout << this->target << " robotomy failed" << std::endl;
}
