#include <iostream>
#include <string>
#include <cstdlib>
#include "../inc/Contact.hpp"
#include "../inc/PhoneBook.hpp"

void getInput(const std::string& prompt, std::string& input)
{    
	while (true) {
        std::cout << prompt;
        if (!std::getline(std::cin, input))
		{
			std::cout << "\nEOF detected. Exiting the program." << std::endl;
			std::exit(130);
        }
		else if (input.empty())
		{
			std::cout << "Input cannot be empty.\n";
        }
		else
            break ;
    }
}

void addNewContact(PhoneBook& phoneBook)
{
    Contact newContact;
    std::string firstName, lastName, nickName;

    getInput("Enter first name: ", firstName);
    newContact.setFirstName(firstName);

    getInput("Enter last name: ", lastName);
    newContact.setLastName(lastName);

    getInput("Enter nickname: ", nickName);
    newContact.setNickName(nickName);

    phoneBook.addContact(newContact);
	std::cout << "Contact added successfully!\n";
}

void searchContact(PhoneBook& phoneBook)
{
    phoneBook.displayContacts();

    int index;
    while (true)
	{
        std::cout << "Enter the index of the contact to view: ";
        if (!(std::cin >> index))
		{
            if (std::cin.eof())
			{
                std::cout << "\nEOF detected. Exiting the program." << std::endl;
				std::exit(130);
			}
			else if (std::cin.fail())
			{
                std::cout << "Error: Please enter a valid integer index." << std::endl;
				std::cin.clear();
				std::cin.ignore(10000, '\n');
			}
        }
		else if (index >= 1 && index <= 8)
		{
			phoneBook.displayContactAt(index);
            break;
		}
		else
		{
			std::cout << "Invalid index or no contact at this index." << std::endl;
			break;
		}
    }
	std::cin.clear();
	std::cin.ignore(10000, '\n');
}

int main()
{
    std::string command;
    PhoneBook phoneBook;

    while (true)
	{
        std::cout << "Enter a command (ADD, SEARCH, EXIT): ";

        if (!std::getline(std::cin, command))
		{
            std::cout << "\nEOF detected. Exiting the program." << std::endl;
            break;
        }

        for (size_t i = 0; i < command.length(); ++i)
            command[i] = std::toupper(command[i]);

        if (command == "ADD")
            addNewContact(phoneBook);
        else if (command == "SEARCH")
            searchContact(phoneBook);
        else if (command == "EXIT") {
            std::cout << "Exiting the program.\n";
            break;
        }
    }
    return (0);
}
