#include "Server.hpp"

// https://ircv3.net/specs/extensions/capability-negotiation.html
void	Server::CAP(t_parser_data& data,User* &user)
{
	return;

	// TODO pas besoin de gerer

	if (data.cmd.size() == 1)
	{
		Numerics::_461_ERR_NEEDMOREPARAMS("*", data.cmd[0], user->get_fd());
		return;
	}
	else
	{
		if (data.cmd[1] == "LS")
		{
			send(user->get_fd(), ":" SERVER_NAME " CAP * LS:\r\n", 12, 0);
			// https://ircv3.net/specs/extensions/capability-negotiation.html#cap-ls-version
		}
	}
}