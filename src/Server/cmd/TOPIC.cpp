#include "Server.hpp"

// https://modern.ircdocs.horse/#topic-message
void	Server::TOPIC(t_parser_data& data, User* &user)
{
	if (data.cmd.size() < 2 || data.cmd.size() > 3)
	{
		Numerics::_461_ERR_NEEDMOREPARAMS(user->get_nickname(), data.cmd[0], user->get_fd());
		return;
	}

	Channel*	channel = this->Channels[data.cmd[1]];

	if (!channel)
	{
		Numerics::_403_ERR_NOSUCHCHANNEL(user->get_nickname(), data.cmd[1], user->get_fd());
		return;
	}

	if (!channel->isUser(user->get_id()))
	{
		Numerics::_442_ERR_NOTONCHANNEL(user->get_nickname(), data.cmd[1], user->get_fd());
		return;
	}

	if (data.cmd.size() == 2)
	{
		if (!channel->getTopic().empty())
		{
			Numerics::_332_RPL_TOPIC( user->get_nickname(), data.cmd[1], channel->getTopic(), user->get_fd());
			Numerics::_333_RPL_TOPICWHOTIME(user->get_nickname(), channel->getName(), channel->getTopic_modif_user(), channel->getTopic_modif_time(), user->get_fd());
		}
		else
			Numerics::_331_RPL_NOTOPIC(user->get_nickname(), data.cmd[1], user->get_fd());
	}
	else
	{
		if (channel->isProtectedTopic() && !channel->isOperator(user->get_id()))
			Numerics::_482_ERR_CHANOPRIVSNEEDED(user->get_nickname(), channel->getName(), user->get_fd());
		else
		{
			channel->setTopic(data.cmd[2]);
			channel->setTopicModifUser(user->get_nickname());
			channel->setTopicModifTime(std::time(NULL));

			std::string msg = ":" + user->get_nickname() + " TOPIC " + channel->getName() + " :" + data.cmd[2] + "\r\n";
			sendToAll(channel->getUser(), msg);
			std::clog << msg;
		}
	}
}