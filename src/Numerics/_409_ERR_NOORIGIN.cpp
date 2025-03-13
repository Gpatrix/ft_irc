#include "Numerics.hpp"

void Numerics::_409_ERR_NOORIGIN(const std::string& client, const int& fd)
{
	std::string msg = ":" SERVER_NAME " 409 " + client + " :No origin specified\r\n";
	send(fd, msg.c_str(), msg.size(), 0);
	logError(msg);
}
