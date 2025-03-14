#include "Numerics.hpp"

void Numerics::_333_RPL_TOPICWHOTIME
(
	const std::string& client,
	const std::string& channel,
	const std::string& nick,
	const std::time_t& time,
	const int& fd
)
{
	static std::stringstream stream;
	stream.clear();
	stream << time;

	std::string msg = ":" SERVER_NAME " 333 " + client + " " + channel + " " + nick + " " + stream.str() + "\r\n";
	send(fd, msg.c_str(), msg.size(), 0);
	log(msg);
}

