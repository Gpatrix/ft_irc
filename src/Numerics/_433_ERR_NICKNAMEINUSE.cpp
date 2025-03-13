#include "Numerics.hpp"

void Numerics::_433_ERR_NICKNAMEINUSE(const std::string& new_nickname, const int& fd)
{
	std::string msg = ":" SERVER_NAME " 433 * " + new_nickname + " :Nickname is already in use\r\n";
	send(fd, msg.c_str(), msg.size(), 0);
	logError(msg);

}
