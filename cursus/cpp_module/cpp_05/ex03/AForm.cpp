/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 13:08:18 by igarcia2          #+#    #+#             */
/*   Updated: 2025/04/18 18:16:43 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"

//Constructor
AForm::AForm() : name("defaultName"), fSigned(false),
	signGrade(150), execGrade(150) {}

AForm::AForm(const AForm &other) : name(other.name), fSigned(other.fSigned),
	signGrade(other.signGrade), execGrade(other.execGrade) {}

AForm::AForm(const std::string& newName, int newSignGrade, int newExecGrade)
	: name(newName), fSigned(false), signGrade(newSignGrade),
	execGrade(newExecGrade)
{
	if (newSignGrade > 150 || newExecGrade > 150)
	{
		throw GradeTooLowException();
	}
	if (newSignGrade < 1 || newExecGrade < 1)
	{
		throw GradeTooHighException();
	}
}

//Destructor
AForm::~AForm() {}

//Operator
AForm& AForm::operator=(const AForm &other)
{
	if (this != &other)
	{
		this->fSigned = other.fSigned;
	}
	return (*this);
}

std::ostream& operator<<(std::ostream &os, const AForm &obj)
{
	os << "Form:" << obj.getName()
		<< (obj.isSigned() ? " signed" : " not signed")
		<< "; signGrade:" << obj.getSignGrade()
		<< "; execGrade:" << obj.getExecGrade();

	return (os);
}

//Getters
const std::string&	AForm::getName() const
{
	return (this->name);
}

bool	AForm::isSigned() const
{
	return (this->fSigned);
}

int	AForm::getSignGrade() const
{
	return (this->signGrade);
}

int	AForm::getExecGrade() const
{
	return (this->execGrade);
}

void	AForm::beSigned(const Bureaucrat &b)
{
	if (b.getGrade() <= this->signGrade)
	{
		this->fSigned = true;
	}
	else
	{
		throw GradeTooLowException();
	}
}

//Setter
void	AForm::setSigned(bool value)
{
	this->fSigned = value;
}

//Exception
const char*	AForm::GradeTooHighException::what() const throw()
{
	return ("Grade is too high!");
}

const char*	AForm::GradeTooLowException::what() const throw()
{
	return ("Grade is too low!");
}

const char*	AForm::FormNotSignedException::what() const throw()
{
	return ("Form is not signed!");
}
