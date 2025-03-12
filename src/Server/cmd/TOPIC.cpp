#include "Server.hpp"

// https://modern.ircdocs.horse/#topic-message
void	Server::TOPIC(t_parser_data& data, User* &user)
{
	if (data.cmd.size() < 2 || data.cmd.size() > 3)
	{
		Numerics::_461_ERR_NEEDMOREPARAMS(data.cmd[0], user->get_fd());
		return;
	}
}