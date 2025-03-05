#pragma once

#include <iostream>

#include "User.hpp"
#include "Channel.hpp"

#include <vector>
#include <map>

#include <sys/poll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/ioctl.h>

#include <cstring>
#include <cstdlib>
#include <cstdio> // for debug perror

#include <unistd.h>

#include <signal.h>

#include <errno.h>

class Server
{
	private:
		std::map<std::string&, Channel&>	Channels;
		std::vector<User*>					Users;
		int									Sockfd;
		std::string							Password;

		std::vector<pollfd>	fds;

		void		init_socket(char* &port);
		inline void	accept_new_user(void);
		inline void	recv_data(short& index, bool& compress_array);
		inline void	compress_fds(void);

	public:
		Server(void);

		~Server(void);
		void	init(char* port, char* password);
		void	run(void);
};
