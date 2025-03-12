#include"Numerics.hpp"

void Numerics::_482_ERR_CHANOPRIVSNEEDED(const std::string& channel, const int& fd)
{
	std::string msg = ":" SERVER_NAME " 482 " + channel + " :You're not channel operator\r\n";
	send(fd, msg.c_str(), msg.size(), 0);
	std::clog << msg;
}
