#pragma once

#include <iostream>

#include "user.hpp"
#include "channel.hpp"

#include <vector>
#include <map>

#include <sys/poll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <poll.h>

#include <cstring>
#include <cstdlib>
#include <cstdio> // for debug perror

#include <unistd.h>

#include <errno.h>

class server
{
	private:
		std::map<std::string&, channel&>	channels;
		std::vector<user*>					user;
		int									sockfd;
		std::string							password;

		pollfd	fds[200];
		short	nfds;

		void	init_socket(char* &port);


	public:
		server(char* port, char* password);
		~server(void);
};
