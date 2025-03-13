#include "Numerics.hpp"

void	Numerics::_464_ERR_PASSWDMISMATCH(const std::string& client, const int& fd)
{
	std::string msg = ":" SERVER_NAME " 464 " + client + " :Password incorrect\r\n";
	send(fd, msg.c_str(), msg.size(), 0);
	logError(msg);
}
