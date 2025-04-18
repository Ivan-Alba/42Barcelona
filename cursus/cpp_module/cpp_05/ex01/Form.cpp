/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 13:08:18 by igarcia2          #+#    #+#             */
/*   Updated: 2025/04/18 14:34:04 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"

//Constructor
Form::Form() : name("defaultName"), fSigned(false),
	signGrade(150), execGrade(150) {}

Form::Form(const Form &other) : name(other.name), fSigned(other.fSigned),
	signGrade(other.signGrade), execGrade(other.execGrade) {}

Form::Form(const std::string& newName, int newSignGrade, int newExecGrade)
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
Form::~Form() {}

//Operator
Form& Form::operator=(const Form &other)
{
	if (this != &other)
	{
		this->fSigned = other.fSigned;
	}
	return (*this);
}

std::ostream& operator<<(std::ostream &os, const Form &obj)
{
	os << "Form:" << obj.getName()
		<< (obj.isSigned() ? " signed" : " not signed")
		<< "; signGrade:" << obj.getSignGrade()
		<< "; execGrade:" << obj.getExecGrade();

	return (os);
}

//Getters
const std::string&	Form::getName() const
{
	return (this->name);
}

bool	Form::isSigned() const
{
	return (this->fSigned);
}

int	Form::getSignGrade() const
{
	return (this->signGrade);
}

int	Form::getExecGrade() const
{
	return (this->execGrade);
}

void	Form::beSigned(const Bureaucrat &b)
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

//Exception
const char*	Form::GradeTooHighException::what() const throw()
{
	return ("Grade is too high!");
}

const char*	Form::GradeTooLowException::what() const throw()
{
	return ("Grade is too low!");
}
