
#include "Numerics.hpp"

void	Numerics::_001_RPL_WELCOME(const std::string& client, const int& fd)
{
	std::string msg = ":" SERVER_NAME " 001 " + client + " :Welcome to the chorizo Network, " + client + "\r\n";
	send(fd, msg.c_str(), msg.size(), 0);
	log(client + " Accepted\n");
}
