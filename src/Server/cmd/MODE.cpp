#include "Server.hpp"

// https://modern.ircdocs.horse/#mode-message
void Server::MODE(t_parser_data& data, User* &user)
{
	if (data.cmd.size() < 2)
	{
		Numerics::_461_ERR_NEEDMOREPARAMS(data.cmd[0], user->get_fd());
		return;
	}
	if (data.cmd[1][0] == '#')
		ChannelMode(data, user);
	else
		UserMode(data, user);
}

void	Server::ChannelMode(t_parser_data& data, User* &user)
{
	Channel*	channel;

	channel = this->Channels[data.cmd[1]];
	if (!channel)
	{
		Numerics::_403_ERR_NOSUCHCHANNEL(data.cmd[1], user->get_fd());
		return;
	}
	if (data.cmd.size() < 3)
	{
		// https://modern.ircdocs.horse/#rplchannelmodeis-324
		return;
	}

	// if (NO ACCESS TO CHNANNEL)
	// {
	// 	// https://modern.ircdocs.horse/#errchanoprivsneeded-482
	// }

	(void)data;
	(void)user;
}

void	Server::UserMode(t_parser_data& data, User* &user)
{
	(void)data;
	(void)user;
}
