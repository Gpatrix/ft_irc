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

void Server::ChannelMode(t_parser_data& data, User* &user)
{
	std::string c = data.cmd[1].substr(1, data.cmd[1].size());
	Channel* channel = this->Channels[c];
	if (!channel)
	{
		Numerics::_403_ERR_NOSUCHCHANNEL(data.cmd[1], user->get_fd());
		return;
	}

	// Vérifier si l'utilisateur est opérateur du channel
	if (!channel->isOperator(user->get_id()))
	{
		Numerics::_482_ERR_CHANOPRIVSNEEDED(data.cmd[1], user->get_fd());
		return;
	}

	std::string modeString = data.cmd[2];
	bool addMode = (modeString[0] == '+');
	size_t argIndex = 3;

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
			case 'k': // Mot de passe
				if (argIndex >= data.cmd.size())
				{
					Numerics::_461_ERR_NEEDMOREPARAMS("MODE", user->get_fd());
					return;
				}
				if (addMode)
					channel->setKey(data.cmd[argIndex++]);
				else
					channel->freeKey();
				break;
			case 'o': // Donner/retirer l'opérateur à un user
				if (argIndex >= data.cmd.size())
				{
					Numerics::_461_ERR_NEEDMOREPARAMS("MODE", user->get_fd());
					return;
				}
				if (User* target = this->find_User(data.cmd[argIndex++]))
					channel->addOperator(target->get_id());
				break;
			case 'l':
				if (addMode)
				{
					if (argIndex >= data.cmd.size())
					{
						Numerics::_461_ERR_NEEDMOREPARAMS("MODE", user->get_fd());
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

	// Annonce aux utilisateurs du channel
	std::string msg = ":" + user->get_nickname() + " MODE " + channel->getName() + " " + modeString;
	this->sendToAll(channel->getUser(),msg);
	std::clog << msg;
}

void Server::UserMode(t_parser_data& data, User* &user)
{
	// Vérifier si c'est l'utilisateur lui-même qui change son mode
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
	std::string msg = ":" + user->get_nickname() + " MODE " + user->get_nickname() + " " + modeString;
	this->sendToAll_Users(msg);
	std::clog << msg;
}

