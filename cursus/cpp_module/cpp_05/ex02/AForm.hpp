/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 13:08:27 by igarcia2          #+#    #+#             */
/*   Updated: 2025/08/14 13:25:33 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AFORM_HPP
# define AFORM_HPP

# include "Bureaucrat.hpp"
# include <string>
# include <iostream>
# include <stdexcept>

class	Bureaucrat;

class	AForm
{
	private:
		const std::string	name;
		bool				fSigned;
		const int			signGrade;
		const int			execGrade;

	public:
		AForm();
		AForm(const AForm &other);
		AForm(const std::string &newName, int newSignGrade, int newExecGrade);
		virtual ~AForm();

		const std::string&	getName() const;
		bool				isSigned() const;
		int					getSignGrade() const;
		int					getExecGrade() const;
		
		void				setSigned(bool value);

		AForm& operator=(const AForm &other);
	
		void	beSigned(const Bureaucrat &b);
		virtual void	execute(Bureaucrat const &executor) const = 0;

		class	GradeTooHighException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};
		
		class	GradeTooLowException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};

		class	FormNotSignedException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};
};

std::ostream& operator<<(std::ostream &os, const AForm &obj);

#endif
