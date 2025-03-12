#include "Server.hpp"

// https://modern.ircdocs.horse/#topic-message
void	Server::TOPIC(t_parser_data& data, User* &user)
{
	if (data.cmd.size() < 2 || data.cmd.size() > 3)
	{
		Numerics::_461_ERR_NEEDMOREPARAMS(data.cmd[0], user->get_fd());
		return;
	}

	Channel*	channel = this->Channels[data.cmd[1]];

	// verif access

	if (!channel)
	{
		Numerics::_403_ERR_NOSUCHCHANNEL(data.cmd[1], user->get_fd());
		return;
	}
	if (data.cmd.size() == 2)
	{
		if (!channel->getTopic().empty())
			Numerics::_332_RPL_TOPIC(data.cmd[1], channel->getTopic(), user->get_fd());
		else
			Numerics::_331_RPL_NOTOPIC(data.cmd[1], user->get_fd());
	}
	else if (data.cmd[2].empty())
	{
		//   TOPIC #test :                   ; Clearing the topic on "#test"
	}
	else
	{
		//  TOPIC #test :New topic          ; Setting the topic on "#test" to
        //                           "New topic".
	}
	
	
}