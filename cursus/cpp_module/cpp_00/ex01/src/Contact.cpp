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

//Constructor
Contact::Contact() : firstName(""), lastName(""), nickName(""), phoneNumber(""),
	darkSecret("") {}

Contact::Contact(std::string& first, std::string &last, std::string &nick,
	std::string &phone, std::string &dark)
{
	this->firstName = first;
	this->lastName = last;
	this->nickName = nick;
	this->phoneNumber = phone;
	this->darkSecret = dark;
}

//Getters
std::string Contact::getFirstName() const
{
	return (firstName);
}

std::string Contact::getLastName() const
{
	return (lastName);
}

std::string Contact::getNickName() const
{
	return (nickName);
}

std::string Contact::getPhoneNumber() const
{
	return (phoneNumber);
}

std::string Contact::getDarkSecret() const
{
	return (darkSecret);
}

//Setters
void	Contact::setFirstName(const std::string& first)
{
	this->firstName = first;
}

void	Contact::setLastName(const std::string& last)
{
	this->lastName = last;
}

void	Contact::setNickName(const std::string& nick)
{
	this->nickName = nick;
}

void	Contact::setPhoneNumber(const std::string& phone)
{
	this->phoneNumber = phone;
}

void	Contact::setDarkSecret(const std::string& dark)
{
	this->darkSecret = dark;
}

void	Contact::displayContact() const
{
	std::cout << "First Name: " << firstName << std::endl;
	std::cout << "Last Name: " << lastName << std::endl;
	std::cout << "Nick Name: " << nickName << std::endl;
}
