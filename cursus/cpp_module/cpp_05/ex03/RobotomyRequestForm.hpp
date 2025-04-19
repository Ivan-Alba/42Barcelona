/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:40:15 by igarcia2          #+#    #+#             */
/*   Updated: 2025/04/18 19:53:17 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROBOTOMYREQUESTFORM_HPP
# define ROBOTOMYREQUESTFORM_HPP

# include "AForm.hpp"

class	RobotomyRequestForm : public AForm
{
	private:
		const std::string	target;

	public:
		RobotomyRequestForm();
		RobotomyRequestForm(const RobotomyRequestForm &other);
		RobotomyRequestForm(const std::string &target);
		~RobotomyRequestForm();

		RobotomyRequestForm& operator=(const RobotomyRequestForm &other);

		void	execute(Bureaucrat const &executor) const;
};

#endif
