#include "Server.hpp"

// https://dd.ircdocs.horse/refs/commands/pass
void	Server::PASS(t_parser_data& data,User* &user)
{
	if (data.cmd.size() != 2)
	{
		// https://modern.ircdocs.horse/#errneedmoreparams-461
		std::clog << "ERROR: need mor param" << '\n';
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