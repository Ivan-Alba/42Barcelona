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
	std::string	getFirstName() const;
	
	std::string	getLastName() const;

	std::string	getNickName() const;

	//Setters
	void	setFirstName(const std::string& first);

	void	setLastName(const std::string& last);

	void	setNickName(const std::string& nick);

	void	displayContact() const;
};

#endif
