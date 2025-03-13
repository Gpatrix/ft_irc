#include "Server.hpp"

// https://modern.ircdocs.horse/#part-message
void Server::PART(t_parser_data& data, User*& user)
{
	if (data.cmd.size() < 2)
	{
		Numerics::_461_ERR_NEEDMOREPARAMS(user->get_nickname(), data.cmd[0], user->get_fd());
		return;
	}

	std::vector<std::string> channel_list = ft_split(data.cmd[1], ',');
	Channel*	channel;
	std::string	msg;

	for (size_t index = 0; index < channel_list.size(); index++)
	{
		channel = this->Channels[channel_list[index]];
		if (!channel)
		{
			Numerics::_403_ERR_NOSUCHCHANNEL(user->get_nickname(), channel_list[index], user->get_fd());
			continue;
		}
		
		if (!channel->isUser(user->get_id()))
		{
			Numerics::_442_ERR_NOTONCHANNEL(user->get_nickname(), channel_list[index], user->get_fd());
			continue;
		}
		
		channel->removeOperator(user->get_id());
		channel->removeUser(user->get_id());

		msg = ":" + user->get_nickname() + " PART " + channel_list[index] + "\r\n";
		sendToAll(channel->getUsers(), msg);
		send(user->get_fd(), msg.c_str(), msg.length(), 0);
	}
}