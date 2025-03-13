#include "Server.hpp"

void Server::JOIN(t_parser_data& data, User* &user)
{
	if (data.cmd.size() < 2)
	{
		Numerics::_461_ERR_NEEDMOREPARAMS(user->get_nickname(), data.cmd[0], user->get_fd());
		return;
	}

	std::vector<std::string> channels = this->ft_split(data.cmd[1]);
	std::vector<std::string> keys = (data.cmd.size() > 2) ? ft_split(data.cmd[2]) : std::vector<std::string>();
	std::string channelName, key;
	
	for (size_t i = 0; i < channels.size(); i++)
	{	
		
		channelName = channels[i];
		key = (i < keys.size()) ? keys[i] : "";
		if (channelName[0] != '#')
		{
			Numerics::_473_ERR_INVITEONLYCHAN(user->get_nickname(), channelName, user->get_fd());
			continue;
		}
		if (Channels.find(channelName) == Channels.end())
			Channels[channelName] = new Channel(channelName, user->get_id());

		Channel &channel = *Channels[channelName];

		if (channel.isInvited(user->get_id()))
		{
			this->joinChannel(channel, channelName, user);
			continue;
		}

		if (channel.getPasword() != key)
		{
			Numerics::_475_ERR_BADCHANNELKEY(user->get_nickname(), channelName, user->get_fd());
			continue;
		}

		if (channel.isInvitationOnly())
		{
			Numerics::_473_ERR_INVITEONLYCHAN(user->get_nickname(), channelName, user->get_fd());
			continue;
		}

		this->joinChannel(channel, channelName, user);
	}
}

void	Server::joinChannel(Channel &channel, const std::string& channelName, User* &user)
{
	if (channel.addUser(user->get_id()))
	{
		Numerics::_471_ERR_CHANNELISFULL(user->get_nickname(), channelName, user->get_fd());
		return;
	}
	channel.removeInvitation(user->get_id());

	sendToAll(channel.getUsers(), ":" + user->get_nickname() + " JOIN " + channelName + "\r\n");

	if (!channel.getTopic().empty())
	{
		Numerics::_332_RPL_TOPIC(	user->get_nickname(),
									channelName,
									channel.getTopic(),
									user->get_fd());

		Numerics::_333_RPL_TOPICWHOTIME(user->get_nickname(),
										channel.getName(),
										channel.getTopic_modif_user(),
										channel.getTopic_modif_time(),
										user->get_fd());
	}

	Numerics::_353_RPL_NAMREPLY(user->get_nickname(), \
								channel.getChannelSymbol(), \
								channelName, \
								channel.getUserList(this->Users), \
								user->get_fd());

	Numerics::_366_RPL_ENDOFNAMES(user->get_nickname(), channelName, user->get_fd());
}