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
		
		static void	_464_ERR_PASSWDMISMATCH(const int& fd);
		static void	_461_ERR_NEEDMOREPARAMS(const std::string& cmd, const int& fd);
		static void	_421_ERR_UNKNOWNCOMMAND(const std::string& cmd, const int& fd);

};