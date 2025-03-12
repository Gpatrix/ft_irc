#include "Server.hpp"

void Server::PING(t_parser_data& data, User*& user)
{
	if (data.cmd.size() != 2)
	{
		// Remplacement par l'erreur correcte (409 ERR_NOORIGIN)
		Numerics::_409_ERR_NOORIGIN(user->get_nickname(), user->get_fd());
		return;
	}

	const std::string& origin = data.cmd[1];
	std::string msg = ":" SERVER_NAME " PONG " SERVER_NAME " :" + origin + "\r\n";

	send(user->get_fd(), msg.c_str(), msg.size(), 0);
}
