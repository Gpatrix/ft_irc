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
		static void _001_RPL_WELCOME(const std::string& client, const int& fd);
		
		static void _324_RPL_CHANNELMODEIS(const std::string& client, const std::string& channel, const std::string& modeString, const std::string& modeArgs, const int& fd);
		static void _331_RPL_NOTOPIC(const std::string& client, const std::string& channel, const int& fd);
		static void _332_RPL_TOPIC(const std::string& client, const std::string& channel, const std::string& topic, const int& fd);
		static void _333_RPL_TOPICWHOTIME(const std::string& client, const std::string& channel, const std::string& nick, const std::time_t& time, const int& fd);
		static void _341_RPL_INVITING(const std::string& client, const std::string& nick, const std::string& channel, const int& fd);
		static void _353_RPL_NAMREPLY(const std::string& client, const std::string& symbol, const std::string& channel, const std::vector<std::string>& users, const int& fd);
		static void _366_RPL_ENDOFNAMES(const std::string& client, const std::string& channel, const int& fd);
		
		static void _401_ERR_NOSUCHNICK(const std::string& client, const std::string& nick, const int& fd);
		static void _403_ERR_NOSUCHCHANNEL(const std::string& client, const std::string& channel, const int& fd);
		static void _404_ERR_CANNOTSENDTOCHAN(const std::string& client, const std::string& channel, const int& fd);
		static void _405_ERR_TOOMANYCHANNELS(const std::string& client, const std::string& channel, const int& fd);
		static void _412_ERR_NOTEXTTOSEND(const std::string& client, const int& fd);
		static void _421_ERR_UNKNOWNCOMMAND(const std::string& client, const std::string& cmd, const int& fd);
		static void _431_ERR_NONICKNAMEGIVEN(const std::string& client, const int& fd);
		static void _432_ERR_ERRONEUSNICKNAME(const std::string& nickname, const int& fd);
		static void _433_ERR_NICKNAMEINUSE(const std::string& new_nickname, const int& fd);
		static void _441_ERR_USERNOTINCHANNEL(const std::string& client, const std::string& channel, const std::string& nick, const int& fd);
		static void _442_ERR_NOTONCHANNEL(const std::string& client, const std::string& channel, const int& fd);
		static void _461_ERR_NEEDMOREPARAMS(const std::string& client, const std::string& cmd, const int& fd);
		static void _462_ERR_ALREADYREGISTERED(const std::string& client, const int& fd);
		static void _464_ERR_PASSWDMISMATCH(const std::string& client, const int& fd);
		static void _471_ERR_CHANNELISFULL(const std::string& client, const std::string& channel, const int& fd);
		static void	_473_ERR_INVITEONLYCHAN(const std::string& client, const std::string& channel, const int& fd);
		static void _475_ERR_BADCHANNELKEY(const std::string& client, const std::string& cmd, const int& fd);
		static void _482_ERR_CHANOPRIVSNEEDED(const std::string& client, const std::string& channel, const int& fd);
		static void _409_ERR_NOORIGIN(const std::string& client, const int& fd);
		static void _443_ERR_USERONCHANNEL(const std::string& client, const std::string& nick, const std::string& channel, const int& fd);
		static void _501_ERR_UMODEUNKNOWNFLAG(const std::string& client, const int& fd);
		static void _502_ERR_USERSDONTMATCH(const std::string& client, const int& fd);

};