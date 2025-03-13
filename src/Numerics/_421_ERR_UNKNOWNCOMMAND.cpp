#include "Numerics.hpp"

void	Numerics::_421_ERR_UNKNOWNCOMMAND(const std::string& cmd, const int& fd)
{
	std::string msg = ":" SERVER_NAME " 421 " + cmd + " :Unknown command\r\n";
	send(fd, msg.c_str(), msg.size(), 0);
	logError("Unknown command\n");
}
