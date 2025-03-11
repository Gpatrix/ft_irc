
#include "Numerics.hpp"

void	Numerics::_001_RPL_WELCOME(const int& fd, const std::string& nick)
{
	std::string msg = ":" SERVER_NAME " 001 " + nick + " :Welcome to the chorizo Network, " + nick + "\r\n";
	send(fd, msg.c_str(), msg.size(), 0);
	std::clog << nick << " Accepted\n";
}
