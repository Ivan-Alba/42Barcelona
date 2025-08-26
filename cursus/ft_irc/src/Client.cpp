#include "Client.hpp"

#include <unistd.h>

// Constructor/Destructor
Client::Client(int fd) : clientFd(fd), nickname(""), username(""),
	passwordAccepted(false), authenticated(false), buffer("") {}

Client::~Client()
{
	if (clientFd >= 0)
	{
		close(clientFd);
		clientFd = -1;
	}
}

// Getter
int	Client::getClientFd() const
{
	return (this->clientFd);
}

const std::string&	Client::getNickname() const
{
	return (this->nickname);
}

const std::string&	Client::getUsername() const
{
	return (this->username);
}

bool	Client::isPasswordAccepted() const
{
	return (this->passwordAccepted);
}

bool	Client::isAuthenticated() const
{
	return (this->authenticated);
}

// Setter
void	Client::setClientFd(int fd)
{
	this->clientFd = fd;
}

void	Client::setNickname(const std::string &nickname)
{
	this->nickname = nickname;
}

void	Client::setUsername(const std::string &username)
{
	this->username = username;
}

void	Client::setPasswordAccepted(bool isAccepted)
{
	this->passwordAccepted = isAccepted;
}

void	Client::setAuthenticated(bool isAuth)
{
	this->authenticated = isAuth;
}


