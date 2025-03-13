#include "Numerics.hpp"

void	Numerics::_473_ERR_INVITEONLYCHAN(const std::string& client, const int& fd)
{
	std::string msg = ":" SERVER_NAME " 473 " + client + " :Cannot join channel (+i)\r\n";
	send(fd, msg.c_str(), msg.size(), 0);
	logError(msg);
}