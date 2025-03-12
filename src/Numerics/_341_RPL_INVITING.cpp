#include "Numerics.hpp"

void Numerics::_341_RPL_INVITING(const std::string& client, const std::string& nick, const std::string& channel, const int& fd)
{
    std::string msg = ":" SERVER_NAME " 341 " + client + " " + nick + " " + channel + "\r\n";
    send(fd, msg.c_str(), msg.size(), 0);
	std::clog << msg;
}
