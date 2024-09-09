/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:39:36 by igarcia2          #+#    #+#             */
/*   Updated: 2024/09/09 15:01:40 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Contact.hpp"

	//Getters
	std::string Contact::getFirstName() const
	{
		return firstName;
	}

	std::string Contact::getLastName() const
	{
		return lastName;
	}

	std::string Contact::getNickName() const
	{
		return nickName;
	}

	//Setters
	void	Contact::setFirstName(const std::string& first)
	{
		firstName = first;
	}

	void	Contact::setLastName(const std::string& last)
	{
		lastName = last;
	}

	void	Contact::setNickName(const std::string& nick)
	{
		nickName = nick;
	}

	void	Contact::displayContact() const
	{
		std::cout << "First Name: " << firstName << std::endl;
		std::cout << "Last Name: " << lastName << std::endl;
		std::cout << "Nick Name: " << nickName << std::endl;
	}
