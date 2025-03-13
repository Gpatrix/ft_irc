#include "Server.hpp"

// https://dd.ircdocs.horse/refs/commands/pass
void	Server::PASS(t_parser_data& data, User* &user)
{
	if (data.cmd.size() != 2)
	{
		Numerics::_461_ERR_NEEDMOREPARAMS("*", data.cmd[0], user->get_fd());
		return;
	}
	else
	{
		if (this->Password == data.cmd[1])
			user->set_have_valid_password(true);
		else
			user->set_have_valid_password(false);
	}
}