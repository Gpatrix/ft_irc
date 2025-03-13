#include "Numerics.hpp"

void	Numerics::_432_ERR_ERRONEUSNICKNAME(const std::string& nickname, const int& fd)
{
	std::string msg = ":" SERVER_NAME " 432 * " + nickname + " :Erroneous nickname\r\n";
	send(fd, msg.c_str(), msg.size(), 0);
	std::clog <<  msg;
}
