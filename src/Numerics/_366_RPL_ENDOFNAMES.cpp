#include "Numerics.hpp"

void Numerics::_366_RPL_ENDOFNAMES(const std::string& channel, const int& fd)
{
	std::string msg = ":" SERVER_NAME " 366 " + channel + " :End of /NAMES list\r\n";
	send(fd, msg.c_str(), msg.size(), 0);
	std::clog << msg;
}
