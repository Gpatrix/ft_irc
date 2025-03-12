#include "Server.hpp"

// https://modern.ircdocs.horse/#mode-message
void Server::MODE(t_parser_data& data, User* &user)
{
	if (data.cmd.size() < 3)
	{
		Numerics::_461_ERR_NEEDMOREPARAMS(data.cmd[0], user->get_fd());
		return;
	}
	if (data.cmd[1][0] == '#')
		ChannelMode(data, user);
	else
		UserMode(data, user);
}

void	Server::ChannelMode(t_parser_data& data,User* &user)
{
	(void)data;
	(void)user;
}

void	Server::UserMode(t_parser_data& data,User* &user)
{
	(void)data;
	(void)user;
}
