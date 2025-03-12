#include "Numerics.hpp"

void	Numerics::_442_ERR_NOTONCHANNEL(const std::string& channel, const int& fd)
{
	std::string msg = ":" SERVER_NAME " 461 " + channel + " :You're not on that channel\r\n";
	send(fd, msg.c_str(), msg.size(), 0);
	std::clog << msg;
}
