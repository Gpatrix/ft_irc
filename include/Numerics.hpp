#pragma once

#include <iostream>
#include <sys/socket.h>
#include "Server.hpp"

class Numerics
{
	private:
		Numerics(void) {};
		~Numerics(void) {};

	public:
		static void	_001_RPL_WELCOME(const int& fd, const std::string& nick);

		static void _332_RPL_TOPIC(const std::string& client, const std::string& channel, const std::string& topic, const int& fd);
		static void _353_RPL_NAMREPLY(const std::string& client, const std::string& symbol, const std::string& channel, const std::vector<std::string>& users, const int& fd);
		static void _366_RPL_ENDOFNAMES(const std::string& client, const std::string& channel, const int& fd);
		
		static void _405_ERR_TOOMANYCHANNELS(const std::string& client, const std::string& channel, const int& fd);
		static void	_464_ERR_PASSWDMISMATCH(const int& fd);
		static void	_461_ERR_NEEDMOREPARAMS(const std::string& cmd, const int& fd);
		static void	_421_ERR_UNKNOWNCOMMAND(const std::string& cmd, const int& fd);
		static void _475_ERR_BADCHANNELKEY(const std::string& cmd, const int& fd);
};