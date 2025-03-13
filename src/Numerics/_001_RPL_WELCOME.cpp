
#include "Numerics.hpp"

void	Numerics::_001_RPL_WELCOME(const int& fd, const std::string& client)
{
	std::string msg = ":" SERVER_NAME " 001 " + client + " :Welcome to the chorizo Network, " + client + "\r\n";
	send(fd, msg.c_str(), msg.size(), 0);
	log(nick + " Accepted\n");
}
