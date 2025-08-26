#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <sys/types.h>
#include <sys/socket.h>
#include <poll.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <string>

namespace	serverConfig
{
	// Server settings
	const std::string	serverName = "ircserv";
	
	// Socket settings
	const int domain = AF_INET; // IPv4
	const int type = SOCK_STREAM; // TCP
	const int protocol = 0; // Default for given type (TCP for SOCK_STREAM)
	const int socketLevel = SOL_SOCKET; // Level for SO_REUSADDR option
	const int addrOpt = SO_REUSEADDR; // Reuse without wait a port
	const int addrValue = 1; // Value to activate option

	// Bind settings
	const int listenAddr = INADDR_ANY; // Listen all interfaces

	// Listen settings
	const int backlog = 10;

	// fcntl settings
	const int fcntlCmd = F_SETFL; // Command to set file descriptor flags
	const int fcntlFlag = O_NONBLOCK; // Non-blocking mode flag

	// poll settings
    const short pollReadEvent = POLLIN;  // Ready to read
    const short pollWriteEvent = POLLOUT; // Ready to write
	const int	pollTimeout = -1; // No timeout, wait for events.
}

#endif
