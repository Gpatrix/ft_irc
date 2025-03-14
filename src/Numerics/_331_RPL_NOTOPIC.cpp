#include "Numerics.hpp"

void Numerics::_331_RPL_NOTOPIC(const std::string& client, const std::string& channel, const int& fd)
{
	std::string msg = ":" SERVER_NAME " 331 " + client + " " + channel + " :No topic is set\r\n";
	send(fd, msg.c_str(), msg.size(), 0);
	log(msg);
}
