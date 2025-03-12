#include "Numerics.hpp"

void Numerics::_462_ERR_ALREADYREGISTERED(const std::string& client, const int& fd)
{
	std::string msg = ":" SERVER_NAME " 462 " + client + " :You may not reregister\r\n";
	send(fd, msg.c_str(), msg.size(), 0);
	std::clog << msg;
}
