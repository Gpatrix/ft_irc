#include "Numerics.hpp"

void	Numerics::_461_ERR_NEEDMOREPARAMS(const std::string& client, const std::string& cmd, const int& fd)
{
	std::string msg = ":" SERVER_NAME " 461 " + client + " " + cmd + " :Not enough parameters\r\n";
	send(fd, msg.c_str(), msg.size(), 0);
	std::clog << msg;
}
