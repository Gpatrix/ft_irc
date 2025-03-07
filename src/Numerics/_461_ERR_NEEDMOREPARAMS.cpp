#include "Numerics.hpp"

void	Numerics::_461_ERR_NEEDMOREPARAMS(const std::string& cmd, const int& fd)
{
	std::string msg = ":localhost 461 " + cmd + " :Not enough parameters\r\n";
	send(fd, msg.c_str(), msg.size(), 0);
	std::clog << msg;
}
