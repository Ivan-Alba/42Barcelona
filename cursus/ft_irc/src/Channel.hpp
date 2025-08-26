#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <string>
#include <set>
#include <map>

class Client;

class Channel
{
	private:
		std::string								name;
		std::string								topic;
		std::string								key;
		std::map<std::string, const Client*>	users;
		std::set<const Client*>					operators;
		int										userLimit;

		Channel(); //Block default constructor

	public:
		// Constructor
		Channel(const std::string &name, const std::string &topic);
		
		// Destructor
		~Channel();

		// Getter
		const std::string&	getName() const;
		const std::string&	getTopic() const;
		const std::string&	getKey() const;
		int					getUserLimit() const;

		// Setter
		void	setTopic(const std::string &newTopic);
		void	setKey(const std::string &newKey);
		void	setUserLimit(int newLimit);

		// Utilities
		void	addUser(const Client* newUser);
		void	addOperator(const Client* newOperator);
		void	removeUser(const std::string &nickname);
		void	removeOperator(const Client* operatr);

};

#endif
