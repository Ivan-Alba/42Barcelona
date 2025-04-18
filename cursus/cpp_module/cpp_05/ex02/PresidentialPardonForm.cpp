/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:49:55 by igarcia2          #+#    #+#             */
/*   Updated: 2025/04/18 20:03:50 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PresidentialPardonForm.hpp"

//Constructor
PresidentialPardonForm::PresidentialPardonForm()
	: AForm("presidentialForm", 25, 5), target("defaultTarget") {}

PresidentialPardonForm::PresidentialPardonForm(
		const PresidentialPardonForm &other)
	: AForm(other.getName(), other.getSignGrade(), other.getExecGrade()),
	target(other.target)
{
	this->setSigned(other.isSigned());
}

PresidentialPardonForm::PresidentialPardonForm(const std::string &target)
	: AForm("presidentialForm", 25, 5), target(target) {}

//Destructor
PresidentialPardonForm::~PresidentialPardonForm() {}

//Operator
PresidentialPardonForm&
	PresidentialPardonForm::operator=(const PresidentialPardonForm &other)
{
	if (this != &other)
	{
		this->setSigned(other.isSigned());
	}
	return (*this);
}

//Other
void	PresidentialPardonForm::execute(Bureaucrat const &executor) const
{
	if (!this->isSigned())
	{
		throw FormNotSignedException();
	}
	if (executor.getGrade() > this->getExecGrade())
	{
		throw GradeTooLowException();
	}
	std::cout << this->target << " has been pardoned by Zaphod Beeblebrox"
		<< std::endl;
}
