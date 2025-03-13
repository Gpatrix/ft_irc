#include "Server.hpp"

// https://modern.ircdocs.horse/#kick-message
void Server::KICK(t_parser_data& data, User* &user)
{
	if (data.cmd.size() < 3 || data.cmd.size() > 4)
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
	if (!channel->isOperator(user->get_id()))
	{
		Numerics::_482_ERR_CHANOPRIVSNEEDED(user->get_nickname(), data.cmd[1], user->get_fd());
		return;
	}

	std::vector<std::string> targets = split(data.cmd[2], ',');
	size_t		targets_nbs = targets.size();
	User*		target_user;
	std::string	msg;
	for (size_t i = 0; i < targets_nbs; i++)
	{
		target_user = find_User(targets[i]);
		if (!target_user || !channel->isUser(target_user->get_id()))
		{
			Numerics::_441_ERR_USERNOTINCHANNEL(user->get_nickname(), data.cmd[1], targets[i], user->get_fd());
			continue;
		}

		msg = ':' + user->get_nickname() + " KICK " + channel->getName() + " " + targets[i];
		if (data.cmd.size() == 4 && !data.cmd[3].empty())
			msg += " " + data.cmd[3];
		msg += "\r\n";

		this->sendToAll(channel->getUsers(), msg);
		channel->removeOperator(target_user->get_id());
		channel->removeUser(target_user->get_id());
	}
}