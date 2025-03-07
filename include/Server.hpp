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

#include "time.h" // TODO remove
#include <iomanip> // TODO remove

// clock_t	_start_time = clock();

// std::cout << std::fixed << std::setprecision(10) <<
// static_cast<double>(clock() - _start_time) / CLOCKS_PER_SEC << '\n';

#include <errno.h>


typedef struct s_parser_data
{
	std::vector<std::string> tag;

	std::string nickname;
	std::string user;
	std::string host;

	std::vector<std::string> cmd;
}			t_parser_data;


class Server
{
	private:
		std::map<std::string&, Channel&>	Channels;
		int									Sockfd;
		std::string							Password;

		id_t						Users_id;
		std::vector<User*>			Users;
		std::vector<pollfd>			fds;
		std::vector<std::string>	data_buffer;

		void		init_socket(char* &port);
		inline void	accept_new_user(void);
		inline void	recv_data(short& index, bool& compress_array);
		inline void	compress_fds(void);
		void		exec_cmd(t_parser_data& data,User* &user);
		void		parser(std::string& data, User* &user);

		void	CAP(t_parser_data& data,User* &user);
		void	NICK(t_parser_data& data,User* &user);
		



	public:
		Server(void);
		~Server(void);

		void	init(char* port, char* password);
		void	run(void);
};

