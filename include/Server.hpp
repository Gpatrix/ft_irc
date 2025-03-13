#pragma once

#include <iostream>

#include "User.hpp"
#include "Channel.hpp"
#include "Numerics.hpp"

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
#include <ctime>

#include "time.h" // TODO for testing to remove
#include <iomanip> // TODO for testing to remove

// clock_t	_start_time = clock();

// std::cout << std::fixed << std::setprecision(10) <<
// static_cast<double>(clock() - _start_time) / CLOCKS_PER_SEC << '\n';

#define SERVER_NAME "chorizo.42"

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
		std::map<std::string, Channel*>		Channels;
		int									Sockfd;
		std::string							Password;

		id_t						Users_id;
		std::vector<User*>			Users;
		std::vector<pollfd>			fds;
		std::vector<std::string>	data_buffer;

		bool						need_compress_fds;

		void	close_connection(const int& fd);

		void		init_socket(char* &port);
		inline void	accept_new_user(void);
		inline void	recv_data(short& index);
		void		compress_fds(void);
		void		exec_cmd(t_parser_data& data,User* &user);
		void		parser(std::string& data, User* &user);
		

		void	ERROR(std::string msg, const int& fd) const;

		void	CAP (t_parser_data& data, User* &user);
		void	NICK(t_parser_data& data, User* &user);
		void	USER(t_parser_data& data, User* &user);
		void	PASS(t_parser_data& data, User* &user);
		void	PING(t_parser_data& data, User* &user);
		void	JOIN(t_parser_data& data, User* &user);
		void	QUIT(t_parser_data& data, User* &user);
		void	MODE(t_parser_data& data, User* &user);
		void	KICK(t_parser_data& data, User* &user);

		void	TOPIC(t_parser_data& data, User* &user);

		void	PRIVMSG(t_parser_data& data, User* &user);

		void	try_register(User* &user);

		void	sendToAll(const std::vector<id_t> &user_list, const std::string &message);
		void 	sendToAll(const std::vector<id_t> &user_list, const std::string &message, const id_t& exeption);
		void	sendToAll_Users(const std::string &message);
		void	sendToAll_Users(const std::string &message, const id_t& exeption);


		User*	find_User(const std::string& user_name);
		User*	find_User(const id_t& user_id);

		std::vector<std::string> split(const std::string &str, char delimiter = ',');

		bool 	isValidNickname(const std::string &nickname);
		bool	isNicknameTaken(const std::string &nickname);

		void	ChannelMode(t_parser_data& data,User* &user);
		void	UserMode(t_parser_data& data,User* &user);
		
	public:
		Server(void);
		~Server(void);

		void	init(char* port, char* password);
		void	run(void);
};

