#include "Numerics.hpp"

void	Numerics::_431_ERR_NONICKNAMEGIVEN(const std::string& client, const int& fd)
{
	std::string msg = ":" SERVER_NAME " 431 " + client + "No nickname given\r\n";
	send(fd, msg.c_str(), msg.size(), 0);
	logError(msg);
}
