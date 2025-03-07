#include "Server.hpp"

// https://modern.ircdocs.horse/#nick-message
void	Server::USER(t_parser_data& data,User* &user)
{

	if (data.cmd.size() != 5)
	{
		// https://modern.ircdocs.horse/#errneedmoreparams-461
		return;
	}
	else if (user->get_is_register() == true)
	{
		// https://modern.ircdocs.horse/#erralreadyregistered-462
	}
	else 
	{
		// The maximum length of <username> may be specified by the USERLEN RPL_ISUPPORT parameter
		if (data.cmd[1].size() < 1)
		{
			// https://modern.ircdocs.horse/#errneedmoreparams-461
			return;
		}
		user->set_username("~" + data.cmd[1]);
		user->set_realname(data.cmd[3]);
	}
}