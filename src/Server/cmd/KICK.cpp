#include "Server.hpp"

#define DEFAULT_MSG "You have been kick from the channel"

// https://modern.ircdocs.horse/#kick-message
void Server::KICK(t_parser_data& data, User* &user)
{
	if (data.cmd.size() < 3 || data.cmd.size() > 4)
	{
		Numerics::_461_ERR_NEEDMOREPARAMS(data.cmd[0], user->get_fd());
		return;
	}

	Channel*	channel = this->Channels[data.cmd[1]];

	if (!channel)
	{
		Numerics::_403_ERR_NOSUCHCHANNEL(data.cmd[1], user->get_fd());
		return;
	}

	if (!channel->isOperator(user->get_id()))
	{
		Numerics::_482_ERR_CHANOPRIVSNEEDED(data.cmd[1], user->get_fd());
		return;
	}
	

}