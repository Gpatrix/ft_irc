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
	std::string msg;
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

			Channel* channel = this->Channels[&target[i][index]];
			

			if (!channel)
			{
				std::clog << "no chanel found" << '\n';
				// https://modern.ircdocs.horse/#errnosuchchannel-403
				continue;
			}

			// :Angel PRIVMSG Wiz :Hello are you receiving this message ?
			msg = ":" + user->get_nickname()
				+ " PRIVMSG " + &target[i][index] + " :" + data.cmd[2] + "\r\n";
			sendToAll(*channel, msg, user->get_id());
			std::clog << msg;
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

void Server::sendToAll(Channel &channel, const std::string &message, const id_t& exeption)
{
	const std::vector<id_t> &users = channel.getUser();
	User	*tmp_user;

	for (size_t i = 0; i < users.size(); i++)
	{
		tmp_user = this->Users[users[i]];
		if (tmp_user->get_id() == exeption)
			continue;

		send(tmp_user->get_fd(), message.c_str(), message.length(), 0);
	}
}