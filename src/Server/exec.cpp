#include "Server.hpp"

void	Server::exec_cmd(t_parser_data& data,User* &user)
{
	// TODO touver une meilleur facon de la faire

	std::clog << "executing\n";
	static void	(Server::*fonctPTR[])(t_parser_data& data,User* &user) = 
	{&Server::CAP, &Server::NICK, &Server::USER, &Server::PASS, &Server::PING};
	static std::string	fonctName[] = 
	{"CAP", "NICK", "USER", "PASS", "PING"};

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
	std::clog << "command not found\n";
	// TODO CMD not found
}

void	Server::try_register(User* &user)
{
	if (!user->get_have_valid_password())
	{
		Numerics::_464_ERR_PASSWDMISMATCH(user->get_fd());
		std::clog << "ERROR: Pasword not valid\n";
		return;
	}
	
	if (user->get_nickname().empty())
	{
		// https://modern.ircdocs.horse/#errnonicknamegiven-431
		std::clog << "Nick not set\n";
		return;
	}
	
	user->set_is_register(true);
	Numerics::_001_RPL_WELCOME(user->get_fd(), user->get_nickname());
}

// https://ircv3.net/specs/extensions/capability-negotiation.html
