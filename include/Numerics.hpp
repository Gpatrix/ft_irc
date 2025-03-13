#pragma once

#include <iostream>
#include <ctime>
#include <sys/socket.h>
#include "Server.hpp"

class Numerics
{
	private:
		Numerics(void) {};
		~Numerics(void) {};

	public:
		static void	_001_RPL_WELCOME(const int& fd, const std::string& nick);

		static void _331_RPL_NOTOPIC(const std::string& channel, const int& fd);
		static void _332_RPL_TOPIC(const std::string& channel, const std::string& topic, const int& fd);
		static void _333_RPL_TOPICWHOTIME(const std::string& client, const std::string& channel, const std::string& nick, const std::time_t& time, const int& fd);
		static void _353_RPL_NAMREPLY(const std::string& client, const std::string& symbol, const std::string& channel, const std::vector<std::string>& users, const int& fd);
		static void _366_RPL_ENDOFNAMES(const std::string& client, const std::string& channel, const int& fd);
		
		static void _401_ERR_NOSUCHNICK(const std::string& nick, const int& fd);
		static void _403_ERR_NOSUCHCHANNEL(const std::string& channel, const int& fd);
		static void _404_ERR_CANNOTSENDTOCHAN(const std::string& channel, const int& fd);
		static void _405_ERR_TOOMANYCHANNELS(const std::string& client, const std::string& channel, const int& fd);
		static void _412_ERR_NOTEXTTOSEND(const int& fd);
		static void _421_ERR_UNKNOWNCOMMAND(const std::string& cmd, const int& fd);
		static void _432_ERR_ERRONEUSNICKNAME(const std::string& client, const std::string& nickname, const int& fd);
		static void _433_ERR_NICKNAMEINUSE(const std::string& new_nickname, const int& fd);
		static void _441_ERR_USERNOTINCHANNEL(const std::string& channel, const std::string& nick, const int& fd);
		static void _442_ERR_NOTONCHANNEL(const std::string& channel, const int& fd);
		static void _461_ERR_NEEDMOREPARAMS(const std::string& cmd, const int& fd);
		static void _464_ERR_PASSWDMISMATCH(const int& fd);
		static void _475_ERR_BADCHANNELKEY(const std::string& cmd, const int& fd);
		static void _482_ERR_CHANOPRIVSNEEDED(const std::string& channel, const int& fd);

};