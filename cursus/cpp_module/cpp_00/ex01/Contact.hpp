#ifndef CONTACT_HPP
# define CONTACT_HPP

# include <iostream>
# include <string>

class Contact {
private:
    std::string	firstName;
    std::string	lastName;
    std::string	nickName;

public:
	Contact() : firstName(""), lastName(""), nickName("") {}

	Contact(std::string first, std::string last, std::string nick)
        : firstName(first), lastName(last), nickName(nick) {}

	//Getters
	std::string getFirstName() const
	{
		return firstName;
	}

	std::string getLastName() const
	{
		return lastName;
	}

	std::string getNickName() const
	{
		return nickName;
	}

	//Setters
	void	setFirstName(const std::string& first)
	{
		firstName = first;
	}

	void	setLastName(const std::string& last)
	{
		lastName = last;
	}

	void	setNickName(const std::string& nick)
	{
		nickName = nick;
	}

	void	displayContact() const
	{
		std::cout << "First Name: " << firstName << std::endl;
		std::cout << "Last Name: " << lastName << std::endl;
		std::cout << "Nick Name: " << nickName << std::endl;
	}
};

#endif
