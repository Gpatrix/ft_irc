#include "Server.hpp"

// https://modern.ircdocs.horse/#mode-message
void Server::MODE(t_parser_data& data, User* &user)
{
	if (data.cmd.size() < 2)
	{
		Numerics::_461_ERR_NEEDMOREPARAMS(user->get_nickname(), data.cmd[0], user->get_fd());
		return;
	}
	if (data.cmd[1][0] == '#')
		ChannelMode(data, user);
	else
		UserMode(data, user);
}

void Server::ChannelMode(t_parser_data& data, User* &user)
{
	Channel* channel = this->Channels[data.cmd[1]];
	if (!channel)
	{
		Numerics::_403_ERR_NOSUCHCHANNEL(user->get_nickname(), data.cmd[1], user->get_fd());
		return;
	}

	if (data.cmd.size() == 2)
	{
		Numerics::_324_RPL_CHANNELMODEIS(user->get_nickname(), channel->getName(), channel->getModeString(), channel->getModeArgs(), user->get_fd());
		return;
	}
	if (!channel->isOperator(user->get_id()))
	{
		Numerics::_482_ERR_CHANOPRIVSNEEDED(user->get_nickname(), data.cmd[1], user->get_fd());
		return;
	}
	std::string modeString = data.cmd[2];
	bool addMode = (modeString[0] == '+');
	size_t argIndex = 3;
	std::string	target_str;

	for (size_t i = 1; i < modeString.length(); i++)
	{
		char mode = modeString[i];

		switch (mode)
		{
			case 'i':
				channel->setInvitationOnly(addMode);
				break;
			case 't': 
				channel->setProtectedTopic(addMode);
				break;
			case 'k':
				if (argIndex >= data.cmd.size())
				{
					Numerics::_461_ERR_NEEDMOREPARAMS(user->get_nickname(), "MODE", user->get_fd());
					return;
				}
				if (addMode)
					channel->setKey(data.cmd[argIndex++]);
				else
					channel->clearKey();
				break;
			case 'o':
				if (argIndex >= data.cmd.size())
				{
					Numerics::_461_ERR_NEEDMOREPARAMS(user->get_nickname(), "MODE", user->get_fd());
					return;
				}
				if (User* target = this->find_User(data.cmd[argIndex++]))
				{
					if (channel->isUser(target->get_id()))
					{
						target_str = " " + target->get_nickname();
						if (addMode)
							channel->addOperator(target->get_id());
						else
							channel->removeOperator(target->get_id());
					}
				}
				break;
			case 'l':
				if (addMode)
				{
					if (argIndex >= data.cmd.size())
					{
						Numerics::_461_ERR_NEEDMOREPARAMS(user->get_nickname(), "MODE", user->get_fd());
						return;
					}
					channel->setUserLimit(atoi(data.cmd[argIndex++].c_str()));
				}
				else
					channel->setUserLimit(0);
				break;
			default:
				Numerics::_501_ERR_UMODEUNKNOWNFLAG(user->get_nickname(), user->get_fd());
				break;
		}
	}

	std::string msg = ":" + user->get_nickname() + " MODE " + channel->getName() + " " + modeString + target_str +"\r\n";
	this->sendToAll(channel->getUsers(),msg);
	log(msg);
}

void Server::UserMode(t_parser_data& data, User* &user)
{
	if (data.cmd[1] != user->get_nickname())
	{
		Numerics::_502_ERR_USERSDONTMATCH(user->get_nickname(), user->get_fd());
		return;
	}

	std::string modeString = data.cmd[2];
	bool addMode = (modeString[0] == '+');
	for (size_t i = 1; i < modeString.length(); i++)
	{
		char mode = modeString[i];
		switch (mode)
		{
			case 'i':
				user->set_is_invisible(addMode);
				break;
			default:
				Numerics::_501_ERR_UMODEUNKNOWNFLAG(user->get_nickname(), user->get_fd());
				break;
		}
	}
	std::string msg = ":" + user->get_nickname() + " MODE " + user->get_nickname() + " " + modeString + "\r\n";
	send(user->get_fd(), msg.c_str(), msg.length(), 0);
	log(msg);
}

