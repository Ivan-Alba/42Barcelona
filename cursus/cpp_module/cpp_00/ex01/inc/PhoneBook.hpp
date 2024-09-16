#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

# include "Contact.hpp"
# include <iostream>
# include <iomanip>

# define MAX_CONTACTS 8

class PhoneBook {
private:
    Contact	contacts[MAX_CONTACTS];
    int		nextIndex;

public:
	PhoneBook() : nextIndex(0) {}

	void		addContact(const Contact& newContact);
	void		displayContacts() const;
	void		displayContactAt(int index) const;
	std::string	truncate(const std::string& str) const;
};

#endif
