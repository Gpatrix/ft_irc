#include"Numerics.hpp"

void Numerics::_441_ERR_USERNOTINCHANNEL(const std::string& channel, const std::string& nick, const int& fd)
{
	std::string msg = ":" SERVER_NAME " 441 " + nick + " " + channel + " :They aren't on that channel\r\n";
	send(fd, msg.c_str(), msg.size(), 0);
	logError(msg);
}
