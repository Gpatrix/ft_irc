#include "Numerics.hpp"

void Numerics::_324_RPL_CHANNELMODEIS(const std::string& client, const std::string& channel, const std::string& modeString, const std::string& modeArgs, const int& fd)
{
    std::string msg = ":" SERVER_NAME " 324 " + client + " " + channel + " " + modeString;
    if (!modeArgs.empty())
        msg += " " + modeArgs;
    msg += "\r\n";
    send(fd, msg.c_str(), msg.size(), 0);
	log(msg);
}
