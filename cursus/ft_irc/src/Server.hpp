#ifndef SERVER_HPP
#define SERVER_HPP

#include <string>
#include <map>
#include <vector>
#include <poll.h>

class Channel;
class Client;

class Server
{
	private:
		int								listenFd;
		int								port;
		std::string						password;
		std::map<std::string, Channel*>	channels;
		std::map<std::string, Client*>	clientsByNick;
		std::map<int, Client*>			clientsByFd;
		std::vector<struct pollfd>		pollFds;
		
		Server(); // Block default constructor

	public:
		// Constructor
		Server(int port, const std::string &password);
		
		// Destructor
		~Server();

		// Execution flow
		void	run();
		void	acceptNewClient();
		void	handleClientMessage(int fd);

		// Utilities
		//void	deleteClient(int fd);
		//void	addChannel(const Channel* newChannel);
		//void	deleteChannel(const std::string &channelName);

		void	addPollFd(int fd);
		void	removePollFd(int fd);
		void	disconnectClient(Client *client, const std::string &reason);
		void	sendNotice(const Client *client, const std::string &text);	
		void	sendError(const Client *client, const std::string &text);
		void	sendPrivMsg(const Client *from, const Client* to, const std::string &text);
		void	sendToClient(int clientFd, const std::string &message);

};

#endif
