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

    void addContact(const Contact& newContact) {
        contacts[nextIndex] = newContact;
        nextIndex = (nextIndex + 1) % MAX_CONTACTS;
    }

    void displayContacts() const {
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

    void displayContactAt(int index) const {
        if (index < 1 || index > MAX_CONTACTS || contacts[index - 1].getFirstName().empty()) {
            std::cout << "Invalid index or no contact at this index." << std::endl;
            return;
        }

        const Contact& contact = contacts[index - 1];
        std::cout << "First Name: " << contact.getFirstName() << std::endl;
        std::cout << "Last Name: " << contact.getLastName() << std::endl;
        std::cout << "Nick Name: " << contact.getNickName() << std::endl;
    }
};

#endif
