#include "Numerics.hpp"

void	Numerics::_471_ERR_CHANNELISFULL(const std::string& client, const std::string& channel, const int& fd)
{
	std::string msg = ":" SERVER_NAME " 471 " + client + " " + channel + " :Cannot join channel (+l)\r\n";
	send(fd, msg.c_str(), msg.size(), 0);
	logError(msg);
}