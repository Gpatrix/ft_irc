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
#include <poll.h>

#include <cstring>
#include <cstdlib>
#include <cstdio> // for debug erno

class server
{
	private:
		std::map<std::string&, channel&>	channels;
		std::vector<user*>					user;
		int									sockfd;
		std::string							password;

	public:
		server(char* port, char* password);
		~server(void);
};
