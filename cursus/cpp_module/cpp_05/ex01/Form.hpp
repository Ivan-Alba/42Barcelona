/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 13:08:27 by igarcia2          #+#    #+#             */
/*   Updated: 2025/04/18 14:41:38 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORM_HPP
# define FORM_HPP

# include "Bureaucrat.hpp"
# include <string>
# include <iostream>
# include <stdexcept>

class	Bureaucrat;

class	Form
{
	private:
		const std::string	name;
		bool				fSigned;
		const int			signGrade;
		const int			execGrade;

	public:
		Form();
		Form(const Form &other);
		Form(const std::string &newName, int newSignGrade, int newExecGrade);
		~Form();

		const std::string&	getName() const;
		bool				isSigned() const;
		int					getSignGrade() const;
		int					getExecGrade() const;

		Form& operator=(const Form &other);
	
		void	beSigned(const Bureaucrat &b);

		class	GradeTooHighException : public std::exception
		{
			public:
				const char* what() const throw();
		};
		
		class	GradeTooLowException : public std::exception
		{
			public:
				const char* what() const throw();
		};
};

std::ostream& operator<<(std::ostream &os, const Form &obj);

#endif
