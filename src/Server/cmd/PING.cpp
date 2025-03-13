#include "Server.hpp"

// https://modern.ircdocs.horse/#ping-message
void	Server::PING(t_parser_data& data,User* &user)
{
	if (data.cmd.size() != 2)
	{
		// TODO replace with https://modern.ircdocs.horse/#errnoorigin-409
		Numerics::_461_ERR_NEEDMOREPARAMS(user->get_nickname(), data.cmd[0], user->get_fd());
		return;
	}
	else
	{
		std::string msg = ":" SERVER_NAME " PONG " SERVER_NAME " :" + data.cmd[1] + "\r\n";
		send(user->get_fd(), msg.c_str(), msg.size(), 0);
	}
}