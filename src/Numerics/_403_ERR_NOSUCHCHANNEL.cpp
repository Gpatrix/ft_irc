#include "Numerics.hpp"

void	Numerics::_403_ERR_NOSUCHCHANNEL(const std::string& channel, const int& fd)
{
	std::string msg = ":" SERVER_NAME " 403 " + channel + " :No such channel\r\n";
	send(fd, msg.c_str(), msg.size(), 0);
	logError(msg);
}