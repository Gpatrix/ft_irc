#include "Numerics.hpp"

void	Numerics::_464_ERR_PASSWDMISMATCH(const int& fd)
{
	std::string msg = ":" SERVER_NAME " 464 :Password incorrect\r\n";
	send(fd, msg.c_str(), msg.size(), 0);
	logError("ERROR: Pasword not valid\n");
}
