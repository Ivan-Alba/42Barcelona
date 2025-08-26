#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include "config.hpp"

#include <iostream>
#include <cstring>
#include <vector>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>

//Constructor
Server::Server(int port, const std::string &password) : port(port), password(password)
{
	// Create the server socket
	// int socket(int domain, int type, int protocol);
	// domain/addressFamily: AF_INET (IPv4)
	// type/socketType: SOCK_STREAM (TCP)
	// protocol: 0 (use default for given type, here TCP)
	// return: fd OK / -1 ERROR
	listenFd = socket(serverConfig::domain, serverConfig::type, serverConfig::protocol);

	if (listenFd == -1)
	{
		throw std::runtime_error(
			std::string("socket() failed: ") + strerror(errno));
	}

	// Set socket options
	// int setsocktopt(int sockfd, int level, int optname,
	//					const void *optval, socklen_t optlen);
	// return: 0 OK / -1 ERROR

	if (setsockopt(listenFd, serverConfig::socketLevel, serverConfig::addrOpt,
			&serverConfig::addrValue, sizeof(serverConfig::addrValue)) == -1)
	{
		throw std::runtime_error(
			std::string("setsockopt() failed: ") + strerror(errno));
	}

	// Bind the socket to the specified IP address and port
	//int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
	
	sockaddr_in addr;
	std::memset(&addr, 0, sizeof(addr)); //Clean struct

	addr.sin_family = serverConfig::domain;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = serverConfig::listenAddr;

	if (bind(listenFd, (struct sockaddr*)&addr, sizeof(addr)) == -1)
	{
		throw std::runtime_error(
			std::string("bind() failed: ") + strerror(errno));
	}
	
	// Mark the socket as a passive socket to accept incoming connections
	// int listen(int sockfd, int backlog);
	// return: 0 OK / -1 ERROR

	if (listen(listenFd, serverConfig::backlog) == -1)
	{
		throw std::runtime_error(
			std::string("listen() failed: ") + strerror(errno));
	}

	// Set the listening socket to non-blocking mode
	if (fcntl(listenFd, serverConfig::fcntlCmd, serverConfig::fcntlFlag) == -1)
	{
		throw std::runtime_error(
			std::string("fcntl() fauked: ") + strerror(errno));

	}
}

//Destructor
Server::~Server()
{
	close(listenFd);

	for (std::map<int, Client*>::iterator it = clientsByFd.begin();
		it != clientsByFd.end(); ++it)
	{
    	delete it->second;
	}
	
	clientsByFd.clear();
	clientsByNick.clear();

	for (std::map<std::string, Channel*>::iterator it = channels.begin();
		it != channels.end(); ++it)
	{
    	delete it->second;
	}
	
	channels.clear();
}

// Execution flow
void	Server::run()
{
	addPollFd(listenFd);

	while (true)
	{
		if (poll(&pollFds[0], pollFds.size(), serverConfig::pollTimeout) < 0)	
            throw std::runtime_error("poll() failed");

		for (size_t i = 0; i < pollFds.size(); ++i)
		{
			if (pollFds[i].revents & POLLIN) // Data to read
			{
				if (pollFds[i].fd == listenFd)	// Server poll
				{
					try
					{
						acceptNewClient();
					}
					catch (const std::exception &e)
					{
						std::cerr << "Error: " << e.what() << std::endl;
					}		
				}
				else // Client poll
				{
					handleClientMessage(pollFds[i].fd);
				}
			}
		}
	}
}

void	Server::acceptNewClient()
{
	int					clientFd;
	struct sockaddr_in	clientAddr;
	socklen_t			clientLen;

	clientLen = sizeof(clientAddr);
	clientFd = accept(listenFd, (struct sockaddr*)&clientAddr, &clientLen);
	if (clientFd == -1)
	{
		if (errno != EAGAIN && errno != EWOULDBLOCK)
			throw std::runtime_error(
				std::string("Cannot accept client: ") + strerror(errno));
	}
	else
	{
		std::cout << "New Client accepted" << std::endl;
		Client *newClient = new Client(clientFd);
		clientsByFd[clientFd] = newClient;
		addPollFd(clientFd);
		sendToClient(clientFd, "Enter nickname: "); //Debug
	}
}

void	Server::handleClientMessage(int fd)
{
	(void)fd;
}

// Utilities
void	Server::disconnectClient(Client *client, const std::string& reason)
{
	try
	{
		sendError(client, reason);
	} catch (...) {}

	// Close Client fd
	if (client->getClientFd() >= 0)
	{
		close(client->getClientFd());
		client->setClientFd(-1);
	}

    removePollFd(client->getClientFd());

	// Remove from server
    clientsByFd.erase(client->getClientFd());
    if (!client->getNickname().empty())
	{
		clientsByNick.erase(client->getNickname());
	}

	// Remove from channels
	for (std::map<std::string, Channel*>::iterator it = channels.begin();
		it != channels.end(); ++it)
	{
		Channel* chan = it->second;
		if (chan)
		{
			chan->removeUser(client->getNickname());
			chan->removeOperator(client);
		}
	}

	//Free memory
	delete client;
}

void	Server::addPollFd(int fd)
{
	struct pollfd	newPoll;

	newPoll.fd = fd;
	newPoll.events = serverConfig::pollReadEvent;
	pollFds.push_back(newPoll);
}

void	Server::removePollFd(int fd)
{
	for (size_t i = 0; i < pollFds.size(); ++i)
	{
		if (pollFds[i].fd == fd)
		{
			pollFds[i] = pollFds.back();
			pollFds.pop_back();
			return ;
		}
	}
}

void	Server::sendNotice(const Client *client, const std::string &text)
{
	std::string	msg;

	msg = ":" + serverConfig::serverName + " NOTICE " + client->getNickname()
		+ " :" + text + "\r\n";

	sendToClient(client->getClientFd(), msg);
}

void	Server::sendError(const Client *client, const std::string &text)
{
	std::string	msg;

	msg = "ERROR :" + text + "\r\n";

    sendToClient(client->getClientFd(), msg);
}

void	Server::sendPrivMsg(const Client* from, const Client* to,
	const std::string &text)
{
	std::string	msg;

	msg = ":" + from->getNickname() + " PRIVMSG " + to->getNickname()
		+ " :" + text + "\r\n";

	sendToClient(to->getClientFd(), msg);
}

void	Server::sendToClient(int clientFd, const std::string &message)
{
	ssize_t	bytesSent = send(clientFd, message.c_str(), message.size(), 0);

	if (bytesSent == -1)
	{
		if (errno != EAGAIN && errno != EWOULDBLOCK)
		{
			disconnectClient(clientsByFd.at(clientFd), "Cannot send message.");
			throw std::runtime_error("Error sending to client fd " + clientFd);
		}
    }
}
