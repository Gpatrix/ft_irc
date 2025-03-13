#include"Numerics.hpp"

void Numerics::_475_ERR_BADCHANNELKEY(const std::string& cmd, const int& fd)
{
	std::string msg = ":" SERVER_NAME " 475 " + cmd + " :Cannot join channel (+k)\r\n";
	send(fd, msg.c_str(), msg.size(), 0);
	logError(msg);
}
