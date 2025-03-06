#include "Server.hpp"



void	Server::exec_cmd(t_parser_data& data,User* &user)
{
	static void	(Server::*fonctPTR[4])(t_parser_data& data,User* &user) = {&Server::CAP};
	static std::string	fonctName[] = {"CAP"};

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


// https://ircv3.net/specs/extensions/capability-negotiation.html
