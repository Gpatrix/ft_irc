#include "Numerics.hpp"

void Numerics::_501_ERR_UMODEUNKNOWNFLAG(const std::string& client, const int& fd)
{
	std::string msg = ":" SERVER_NAME " 501 " + client + " :Unknown MODE flag\r\n";
	send(fd, msg.c_str(), msg.size(), 0);
	std::clog << msg;
}
