#include "Numerics.hpp"

void Numerics::_332_RPL_TOPIC(const std::string& client, const std::string& channel, const std::string& topic, const int& fd)
{
	std::string msg = ":" SERVER_NAME " 332 " + client + " " + channel + " :" + topic + "\r\n";
	send(fd, msg.c_str(), msg.size(), 0);
	std::clog << msg;
}
