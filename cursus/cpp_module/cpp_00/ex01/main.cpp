#include <iostream>
#include <string>
#include "Contact.hpp"
#include "PhoneBook.hpp"

void addNewContact(PhoneBook& phoneBook) {
    Contact newContact;
    std::string firstName, lastName, nickName;

    std::cout << "Enter first name: ";
    std::getline(std::cin, firstName);
    newContact.setFirstName(firstName);

    std::cout << "Enter last name: ";
    std::getline(std::cin, lastName);
    newContact.setLastName(lastName);

    std::cout << "Enter nickname: ";
    std::getline(std::cin, nickName);
    newContact.setNickName(nickName);

    phoneBook.addContact(newContact);
    std::cout << "Contact added successfully!\n";
}

int main() {
    std::string command;
    PhoneBook phoneBook;

    while (true) {
        std::cout << "Enter a command (ADD, SEARCH, EXIT): ";

        if (!std::getline(std::cin, command)) {
            std::cout << "\nEOF detected. Exiting the program." << std::endl;
            break;
        }

        for (size_t i = 0; i < command.length(); ++i) {
            command[i] = std::toupper(command[i]);
        }

        if (command == "ADD") {
            addNewContact(phoneBook);
        } 
        else if (command == "SEARCH") {
            phoneBook.displayContacts();

            int index;
            std::cout << "Enter the index of the contact to view: ";
            std::cin >> index;
            std::cin.ignore(); // To ignore the newline character left in the buffer

            phoneBook.displayContactAt(index);
        } 
        else if (command == "EXIT") {
            std::cout << "Exiting the program.\n";
            break;
        } 
        else {
            std::cout << "Error: Invalid command. Please enter ADD, SEARCH, or EXIT.\n";
        }
    }
    return 0;
}
