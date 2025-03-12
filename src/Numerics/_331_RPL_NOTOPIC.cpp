#include "Numerics.hpp"

void Numerics::_331_RPL_NOTOPIC(const std::string& channel, const int& fd)
{
	std::string msg = ":" SERVER_NAME " 332 " + channel + " :No topic is set\r\n";
	send(fd, msg.c_str(), msg.size(), 0);
	std::clog << msg;
}
