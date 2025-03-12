#include "Server.hpp"

// https://modern.ircdocs.horse/#privmsg-message
void Server::PRIVMSG(t_parser_data& data, User* &user)
{
	if (data.cmd.size() != 3)
	{
		if (data.cmd.size() == 2)
			Numerics::_412_ERR_NOTEXTTOSEND(user->get_fd());
		else
			Numerics::_461_ERR_NEEDMOREPARAMS(data.cmd[0], user->get_fd());

		return;
	}

	int	index;
	User*	target_user;
	std::string	msg;
	std::vector<std::string>	target = this->split(data.cmd[1]);
	for (size_t i = 0; i < target.size(); i++)
	{
		index = 0;
		if (target[i][index] == '@')
			index++;
		if (target[i][index] == '%')
			index++;

		msg = ":" + user->get_nickname() + " PRIVMSG " + &target[i][index] + " :" + data.cmd[2] + "\r\n";

		if (target[i][index] == '#')
		{
			// TODO if no acces to chanel https://modern.ircdocs.horse/#errcannotsendtochan-404
			Channel* channel = this->Channels[&target[i][index]];

			if (!channel)
			{
				Numerics::_403_ERR_NOSUCHCHANNEL(&target[i][index], user->get_fd());
				continue;
			}

			sendToAll((*channel).getUser(), msg, user->get_id());
			std::clog << msg;
		}
		else
		{
			target_user = find_User(&target[i][index]);
			if (user == NULL)
			{
				Numerics::_401_ERR_NOSUCHNICK(&target[i][index], user->get_fd());
				continue;
			}
			send(target_user->get_fd(), msg.c_str(), msg.length(), 0);
		}
	}
}


void Server::sendToAll(const std::vector<id_t> &user_list, const std::string &message)
{
	for (size_t i = 0; i < user_list.size(); i++)
		send(this->Users[user_list[i]]->get_fd(), message.c_str(), message.length(), 0);
}

void Server::sendToAll(const std::vector<id_t> &user_list, const std::string &message, const id_t& exeption)
{
	User	*tmp_user;

	for (size_t i = 0; i < user_list.size(); i++)
	{
		tmp_user = this->Users[user_list[i]];
		if (tmp_user->get_id() == exeption)
			continue;

		send(tmp_user->get_fd(), message.c_str(), message.length(), 0);
	}
}