#include "Numerics.hpp"

void Numerics::_502_ERR_USERSDONTMATCH(const std::string& client, const int& fd)
{
	std::string msg = ":" SERVER_NAME " 502 " + client + " :Cant change mode for other users\r\n";
	send(fd, msg.c_str(), msg.size(), 0);
	std::clog << msg;
}
