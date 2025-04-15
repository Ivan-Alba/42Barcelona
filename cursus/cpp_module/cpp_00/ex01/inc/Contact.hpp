#ifndef CONTACT_HPP
# define CONTACT_HPP

# include <iostream>
# include <string>

class	Contact
{
	private:
		std::string	firstName;
		std::string	lastName;
		std::string	nickName;
		std::string	phoneNumber;
		std::string	darkSecret;

	public:
		Contact();

		Contact(std::string &first, std::string &last, std::string &nick,
		std::string &phone, std::string &dark);

		//Getter
		std::string	getFirstName() const;
		std::string	getLastName() const;
		std::string	getNickName() const;
		std::string	getPhoneNumber() const;
		std::string	getDarkSecret() const;

		//Setter
		void	setFirstName(const std::string& first);
		void	setLastName(const std::string& last);
		void	setNickName(const std::string& nick);
		void	setPhoneNumber(const std::string& phone);
		void	setDarkSecret(const std::string& dark);

		void	displayContact() const;
};

#endif
