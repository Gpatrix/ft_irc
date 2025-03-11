#include "Server.hpp"

void Server::JOIN(t_parser_data& data, User* &user)
{
	if (data.cmd.size() < 2)
	{
		Numerics::_461_ERR_NEEDMOREPARAMS(data.cmd[0], user->get_fd());
		return;
	}

	// Séparer les canaux et les clés
	std::vector<std::string> channels = this->split(data.cmd[1]);
	std::vector<std::string> keys;
	if (data.cmd.size() > 2)
		keys = split(data.cmd[2]);


	std::string channelName, key;
	for (size_t i = 0; i < channels.size(); i++)
	{
		channelName = channels[i];
		key = (i < keys.size()) ? keys[i] : "";

		if (Channels.find(channelName) == Channels.end())
			Channels[channelName] = new Channel(channelName, user->get_id());

		Channel &channel = *Channels[channelName];

		if (channel.getPasword() != key)
		{
			Numerics::_475_ERR_BADCHANNELKEY(channelName, user->get_fd());
			continue;
		}

		if (channel.getUser().empty())
			channel.addOperator(user->get_id());
		channel.addUser(user->get_id());

		// TODO remplacer par PRIVMSG
		sendToAll(channel, ":" + user->get_nickname() + " JOIN " + channelName);

		// Envoyer le sujet et la liste des utilisateurs
		if (!channel.getTopic().empty())
			Numerics::_332_RPL_TOPIC(user->get_nickname(), \
										channelName, \
										channel.getTopic(), \
										user->get_fd());

		Numerics::_353_RPL_NAMREPLY(user->get_nickname(), \
									channel.getChannelSymbol(), \
									channelName, \
									channel.getUserList(this->Users), \
									user->get_fd());

		Numerics::_366_RPL_ENDOFNAMES(user->get_nickname(), channelName, user->get_fd());
	}
}
