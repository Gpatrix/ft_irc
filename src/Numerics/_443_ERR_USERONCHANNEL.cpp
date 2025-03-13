#include "Numerics.hpp"

void Numerics::_443_ERR_USERONCHANNEL(const std::string& client, const std::string& nick, const std::string& channel, const int& fd)
{
    std::string msg = ":" SERVER_NAME " 443 " + client + " " + nick + " " + channel + " :is already on channel\r\n";
    send(fd, msg.c_str(), msg.size(), 0);
	logError(msg);
}
