#include "Numerics.hpp"

void Numerics::_405_ERR_TOOMANYCHANNELS(const std::string& client,const std::string& channel, const int& fd)
{
	std::string msg = ":" SERVER_NAME " 405 " + client + " "+ channel + " :You have joined too many channels\r\n";
	send(fd, msg.c_str(), msg.size(), 0);
	logError(msg);
}