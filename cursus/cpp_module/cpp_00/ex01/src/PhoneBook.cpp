/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:26:52 by igarcia2          #+#    #+#             */
/*   Updated: 2024/09/16 12:01:54 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/PhoneBook.hpp"

void	PhoneBook::addContact(const Contact& newContact)
{
	contacts[nextIndex] = newContact;
	nextIndex = (nextIndex + 1) % MAX_CONTACTS;
}

void	PhoneBook::displayContacts() const
{
	std::cout << "PhoneBook Contacts:\n";
	std::cout << std::setw(10) << "Index" << " | "
		<< std::setw(10) << "First Name" << " | "
		<< std::setw(10) << "Last Name" << " | "
		<< std::setw(10) << "Nickname" << std::endl;

	for (int i = 0; i < MAX_CONTACTS; ++i) {
		if (contacts[i].getFirstName().empty()) {
			continue;
		}
		std::cout << std::setw(10) << i + 1 << " | "
			<< std::setw(10) << truncate(contacts[i].getFirstName()) << " | "
			<< std::setw(10) << truncate(contacts[i].getLastName()) << " | "
			<< std::setw(10) << truncate(contacts[i].getNickName()) << std::endl;
	}
}

void	PhoneBook::displayContactAt(int index) const 
{
	if (index < 1 || index > MAX_CONTACTS || contacts[index - 1].getFirstName().empty())
	{
		std::cout << "Invalid index or no contact at this index." << std::endl;
		return;
	}
	const Contact& contact = contacts[index - 1];
	std::cout << "First Name: " << contact.getFirstName() << std::endl;
	std::cout << "Last Name: " << contact.getLastName() << std::endl;
	std::cout << "Nick Name: " << contact.getNickName() << std::endl;
}
