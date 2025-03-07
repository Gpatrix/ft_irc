#include "Server.hpp"

void	Server::exec_cmd(t_parser_data& data,User* &user)
{
	static void	(Server::*fonctPTR[4])(t_parser_data& data,User* &user) = 
	{&Server::CAP, &Server::NICK, &Server::USER};
	static std::string	fonctName[] = 
	{"CAP", "NICK", "USER"};

	static size_t	fonct_size = sizeof(fonctName) / sizeof(std::string);

	static size_t index;

	for (index = 0; index < fonct_size; index++)
	{
		if (data.cmd[0] == fonctName[index])
		{
			(this->*fonctPTR[index])(data, user);
			return;
		}
	}
}

void	Server::try_register(User* &user)
{
	if (!user->get_have_valid_password())
	{
		// https://modern.ircdocs.horse/#errpasswdmismatch-464
		std::clog << "pasword not set\n";
		return;
	}
	
	if (!user->get_nickname().empty())
	{
		// https://modern.ircdocs.horse/#errnonicknamegiven-431
		return;
	}
	
	user->set_is_register(true);
	Numerics::_001_RPL_WELCOME(user->get_fd(), user->get_nickname());
}

// https://ircv3.net/specs/extensions/capability-negotiation.html
