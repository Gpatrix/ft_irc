#include "Server.hpp"

// https://modern.ircdocs.horse/#nick-message
void	Server::NICK(t_parser_data& data,User* &user)
{
	if (data.cmd.size() == 1)
	{
		// TODO https://modern.ircdocs.horse/#errnonicknamegiven-431
		return;
	}
	else if (data.cmd.size() == 2) 
	{
		// TODO maybe https://modern.ircdocs.horse/#errerroneusnickname-432

		// TODO to verif https://modern.ircdocs.horse/#errnicknameinuse-433
		if (data.nickname.empty()) // NICK Wiz | Requesting the new nick "Wiz"
		{
			user->set_nickname(data.cmd[1]);
		}
		else 
		{
			// :WiZ NICK Kilroy | WiZ changed his nickname to Kilroy

			// :dan-!d@localhost NICK Mamoped | dan- changed his nickname to Mamoped
		}
	}
			// send(user->get_fd(), "CAP * LS:\r\n", 12, 0);
}