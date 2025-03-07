#include "Numerics.hpp"

void	Numerics::_001_RPL_WELCOME(const int& fd, const std::string& nick)
{
	std::string msg = ":localhost 001 " + nick + ":Welcome to the chorizo Network, " + nick;
	send(fd, msg.c_str(), msg.size(), 0);
}
