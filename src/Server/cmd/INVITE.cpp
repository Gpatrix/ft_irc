#include "Server.hpp"

// https://modern.ircdocs.horse/#invite-message
void Server::INVITE(t_parser_data& data, User*& user)
{
	if (data.cmd.size() != 3)
	{
		Numerics::_461_ERR_NEEDMOREPARAMS(user->get_nickname(), data.cmd[0], user->get_fd());
		return;
	}

	std::string target_nickname = data.cmd[1];
	std::string target_channel = data.cmd[2];

	Channel* channel = this->Channels[target_channel];
	if (channel == NULL)
	{
		Numerics::_403_ERR_NOSUCHCHANNEL(user->get_nickname(), target_channel, user->get_fd());
		return;
	}

	if (!channel->isUser(user->get_id()))
	{
		Numerics::_442_ERR_NOTONCHANNEL(user->get_nickname(), target_channel, user->get_fd());
		return;
	}
	if (channel->isInvitationOnly() && !channel->isOperator(user->get_id()))
	{
		Numerics::_482_ERR_CHANOPRIVSNEEDED(user->get_nickname(), target_channel, user->get_fd());
		return;
	}

	User* target_user = find_User(target_nickname);
	if (target_user == NULL)
	{
		Numerics::_401_ERR_NOSUCHNICK(user->get_nickname(), target_nickname, user->get_fd());
		return;
	}
	if (channel->isUser(target_user->get_id()))
	{
		Numerics::_443_ERR_USERONCHANNEL(user->get_nickname() ,target_nickname, target_channel, user->get_fd());
		return;
	}

	Numerics::_341_RPL_INVITING(user->get_nickname(), target_nickname, target_channel, user->get_fd());

	std::string msg = ":" + user->get_nickname() + " INVITE " + target_nickname + " " + target_channel + "\r\n";
	send(target_user->get_fd(), msg.c_str(), msg.size(), 0);
	log(msg);
}
