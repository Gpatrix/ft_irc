#pragma once

#include <iostream>

#include "user.hpp"
#include "channel.hpp"

#include <vector>
#include <map>

#ifndef _GNU_SOURCE
 #define _GNU_SOURCE
#endif

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

#include <signal.h>

#include <errno.h>

class server
{
	private:
		std::map<std::string&, channel&>	channels;
		std::vector<user*>					user;
		int									sockfd;
		std::string							password;

		static	bool test;
		pollfd	fds[200];
		short	nfds;

		void	init_socket(char* &port);
		inline void	accept_new_user(void);
		inline void	recv_data(short& index, bool& compress_array);


	public:
		server(char* port, char* password);
		~server(void);
};
