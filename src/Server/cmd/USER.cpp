#include "Server.hpp"

void Server::USER(t_parser_data& data, User*& user)
{
	if (data.cmd.size() != 5)
	{
		Numerics::_461_ERR_NEEDMOREPARAMS(data.cmd[0], user->get_fd());
		std::clog << "ERROR: Need more parameters\n";
		return;
	}
	
	if (user->get_is_register())
	{
		Numerics::_462_ERR_ALREADYREGISTERED(user->get_nickname(), user->get_fd());
		return;
	}

	if (data.cmd[1].empty())
	{
		Numerics::_461_ERR_NEEDMOREPARAMS("USER", user->get_fd());
		std::clog << "ERROR: Username too short\n";
		return;
	}
	std::string username = "~" + data.cmd[1];
	user->set_username(username);
	if (data.cmd[3].empty())
	{
		Numerics::_461_ERR_NEEDMOREPARAMS("USER", user->get_fd());
		std::clog << "ERROR: Realname is required\n";
		return;
	}
	user->set_realname(data.cmd[3]);
	try_register(user);
}
