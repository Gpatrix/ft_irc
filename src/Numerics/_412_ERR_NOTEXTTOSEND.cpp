#include "Numerics.hpp"

void	Numerics::_412_ERR_NOTEXTTOSEND(const int& fd)
{
	std::string msg = ":" SERVER_NAME " 412 :No text to send\r\n";
	send(fd, msg.c_str(), msg.size(), 0);
	logError(msg);
}