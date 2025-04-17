#ifndef BUREAUCRAT_HPP
# define BUREAUCRAT_HPP

# include <string>
# include <iostream>
# include <stdexcept>

class	Bureaucrat
{
	private:
		const std::string	name;
		int					grade;

	public:
		Bureaucrat();
		Bureaucrat(const std::string &name, int grade);
		Bureaucrat(const Bureaucrat &other);
		~Bureaucrat();

		Bureaucrat&		operator=(const Bureaucrat &other);

		const std::string&	getName() const;
		int					getGrade() const;

		void	incrementGrade();
		void	decrementGrade();

		class GradeTooHighException : public std::exception
		{
			public:
				const char* what() const throw();
		};

		class GradeTooLowException : public std::exception
		{
			public:
				const char* what() const throw();
		};
};

std::ostream&	operator<<(std::ostream& os, const Bureaucrat &obj);

#endif
