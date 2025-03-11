#include "Server.hpp"

// https://modern.ircdocs.horse/#privmsg-message
void Server::PRIVMSG(t_parser_data& data, User* &user)
{
	if (data.cmd.size() != 3)
	{
		if (data.cmd.size() == 1)
		{
			// https://modern.ircdocs.horse/#errcannotsendtochan-404
		}
		else if (data.cmd.size() == 2)
		{
			// https://modern.ircdocs.horse/#errnotexttosend-412
		}
		else
			Numerics::_461_ERR_NEEDMOREPARAMS(data.cmd[0], user->get_fd());

		return;
	}

	int	index;
	std::vector<std::string> target = this->split(data.cmd[1]);
	std::map<std::string, Channel *>::iterator it;
	for (size_t i = 0; i < target.size(); i++)
	{
		index = 0;
		if (target[i][index] == '@')
			index++;
		if (target[i][index] == '%')
			index++;
		if (target[i][index] == '#')
		{
			// if no acces to chanel https://modern.ircdocs.horse/#errcannotsendtochan-404
			// Channel &channel = find_channel(&target[i][index + 1]);

			Channel* channel = this->Channels[&target[i][index + 1]];
			

			if (!channel)
			{
				// https://modern.ircdocs.horse/#errnosuchchannel-403
				continue;
			}
			sendToAll(*channel, data.cmd[2]);
		}
		else
		{
			// find target
			// send msg to target
		}
		
		
	}
	
}

void Server::sendToAll(Channel &channel, const std::string &message)
{
	const std::vector<id_t> &users = channel.getUser();

	for (size_t i = 0; i < users.size(); i++)
		send(this->Users[users[i]]->get_fd(), message.c_str(), message.length(), 0);
}