#include "Numerics.hpp"

void	Numerics::_401_ERR_NOSUCHNICK(const std::string& client, const std::string& nick, const int& fd)
{
	std::string msg = ":" SERVER_NAME " 401 " + client + " " + nick + " :No such nick\r\n";
	send(fd, msg.c_str(), msg.size(), 0);
	std::clog << msg;
}