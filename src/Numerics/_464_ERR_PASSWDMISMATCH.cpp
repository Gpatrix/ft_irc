#include "Numerics.hpp"

void	Numerics::_464_ERR_PASSWDMISMATCH(const int& fd)
{
	std::string msg = ":localhost 464 :Password incorrect";
	send(fd, msg.c_str(), msg.size(), 0);
}
