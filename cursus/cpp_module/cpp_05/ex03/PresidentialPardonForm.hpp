/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:48:33 by igarcia2          #+#    #+#             */
/*   Updated: 2025/04/18 19:53:00 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRESIDENTIALPARDONFORM_HPP
# define PRESIDENTIALPARDONFORM_HPP

# include "AForm.hpp"

class	PresidentialPardonForm : public AForm
{
	private:
		const std::string	target;

	public:
		PresidentialPardonForm();
		PresidentialPardonForm(const PresidentialPardonForm &other);
		PresidentialPardonForm(const std::string &target);
		~PresidentialPardonForm();

		PresidentialPardonForm& operator=(const PresidentialPardonForm &other);
	
		void	execute(Bureaucrat const &executor) const;
};

#endif
