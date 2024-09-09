#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

# include "Contact.hpp"
# include <iostream>
# include <iomanip>

# define MAX_CONTACTS 8

class PhoneBook {
private:
    Contact contacts[MAX_CONTACTS];
    int nextIndex;

    std::string truncate(const std::string& str) const {
        if (str.length() > 10) {
            return str.substr(0, 9) + ".";
        }
        return str;
    }

public:
	PhoneBook() : nextIndex(0) {}

	void	addContact(const Contact& newContact);
	void	displayContacts() const;
	void	displayContactAt(int index) const;
};

#endif
