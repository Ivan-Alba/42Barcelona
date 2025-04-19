#ifndef INTERN_HPP
# define INTERN_HPP

# include "AForm.hpp"
# include "ShrubberyCreationForm.hpp"
# include "RobotomyRequestForm.hpp"
# include "PresidentialPardonForm.hpp"

class	Intern
{
	private:
		AForm*	(Intern::*functions[3])(const std::string &target) const;

		AForm*	createShrubberyForm(const std::string &target) const;
		AForm*	createPresidentialForm(const std::string &target) const;
		AForm*	createRobotomyForm(const std::string &target) const;

	public:
		Intern();
		Intern(const Intern &other);
		~Intern();

		Intern& operator=(const Intern &other);

		AForm*	makeForm(const std::string &formName,
			const std::string &target) const;
};

#endif
