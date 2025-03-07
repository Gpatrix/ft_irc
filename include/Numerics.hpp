#pragma once

#include <iostream>
#include <sys/socket.h>

class Numerics
{
	private:
		Numerics(void) {};
		~Numerics(void) {};

	public:
		static void	_001_RPL_WELCOME(const int& fd, const std::string& nick);
		
		static void	_464_ERR_PASSWDMISMATCH(const int& fd);
};