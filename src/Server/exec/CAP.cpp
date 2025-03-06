#include "Server.hpp"

// https://ircv3.net/specs/extensions/capability-negotiation.html
void	Server::CAP(t_parser_data& data,User* &user)
{
	if (data.cmd.size() == 1)
	{
		// TODO see error return;
		return;
	}
	else
	{
		if (data.cmd[1] == "LS")
		{
			send(user, "CAP * LS:\r\n", 12, 0);
			// renvoier les info
			// https://ircv3.net/specs/extensions/capability-negotiation.html#cap-ls-version
		}
	}
}