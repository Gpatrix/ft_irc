#include "Numerics.hpp"

void	Numerics::_403_ERR_NOSUCHCHANNEL(const std::string& client, const std::string& channel, const int& fd)
{
	std::string msg = ":" SERVER_NAME " 403 " + client + " " + channel + " :No such channel\r\n";
	send(fd, msg.c_str(), msg.size(), 0);
	std::clog << msg;
}