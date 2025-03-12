#include "Server.hpp"

// https://modern.ircdocs.horse/#nick-message
void Server::NICK(t_parser_data& data, User* &user)
{
	if (data.cmd.size() < 2)
	{
		Numerics::_461_ERR_NEEDMOREPARAMS(data.cmd[0], user->get_fd());
		return;
	}
	std::string& new_nickname = data.cmd[1];

	if (!isValidNickname(new_nickname))
	{
		Numerics::_432_ERR_ERRONEUSNICKNAME(user->get_nickname(), new_nickname, user->get_fd());
		return;
	}
	if (isNicknameTaken(new_nickname))
	{
		Numerics::_433_ERR_NICKNAMEINUSE(new_nickname, user->get_fd());
		return;
	}
	if (user->get_nickname().empty())
		user->set_nickname(new_nickname);
	else
	{
		std::string msg = ":" + user->get_nickname() + " NICK " + new_nickname + "\r\n";
		user->set_nickname(new_nickname);
		this->sendToAll_Users(msg);
		std::clog << msg;
	}
}
