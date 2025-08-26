#include "Channel.hpp"
#include "Client.hpp"

// Constructor
Channel::Channel(const std::string &name, const std::string &topic)
	: name(name), topic(topic), key(""), userLimit(50) {}

// Destructor
Channel::~Channel()
{
	users.clear();
	operators.clear();
}

// Getter
const std::string& Channel::getName() const
{
	return (this->name);
}

const std::string& Channel::getTopic() const
{
	return (this->topic);
}

const std::string& Channel::getKey() const
{
	return (this->key);
}

int	Channel::getUserLimit() const
{
	return (this->userLimit);
}

// Setter
void	Channel::setTopic(const std::string &newTopic)
{
	this->topic = newTopic;
}

void	Channel::setKey(const std::string &newKey)
{
	this->key = newKey;
}

void	Channel::setUserLimit(int newLimit)
{
	this->userLimit = newLimit;
}

// Utilities
void	Channel::addUser(const Client *newUser)
{
	users[newUser->getNickname()] = newUser;
}

void	Channel::addOperator(const Client *newOperator)
{
	operators.insert(newOperator);
}

void	Channel::removeUser(const std::string &nickname)
{
	users.erase(nickname);
}


void	Channel::removeOperator(const Client *operatr)
{
	operators.erase(operatr);
}
