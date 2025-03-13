#include "Numerics.hpp"

void	Numerics::_404_ERR_CANNOTSENDTOCHAN(const std::string& channel, const int& fd)
{
	std::string msg = ":" SERVER_NAME " 404 " + channel + " :msg could not be delivered\r\n";
	send(fd, msg.c_str(), msg.size(), 0);
	logError(msg);
}