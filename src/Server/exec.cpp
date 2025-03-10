#include "Server.hpp"

void Server::exec_cmd(t_parser_data& data, User* &user)
{
	static std::map<std::string, void (Server::*)(t_parser_data& data, User* &user)> commandMap;
	if (commandMap.empty()) {
		commandMap["CAP"] = &Server::CAP;
		commandMap["NICK"] = &Server::NICK;
		commandMap["USER"] = &Server::USER;
		commandMap["PASS"] = &Server::PASS;
		commandMap["PING"] = &Server::PING;
	}

	std::map<std::string, void (Server::*)(t_parser_data& data, User* &user)>::iterator it = commandMap.find(data.cmd[0]);

	if (it != commandMap.end()) {
		(this->*(it->second))(data, user);
	} else {
		Numerics::_421_ERR_UNKNOWNCOMMAND(data.cmd[0], user->get_fd());
	}
}

void	Server::try_register(User* &user)
{
	if (!user->get_have_valid_password())
	{
		Numerics::_464_ERR_PASSWDMISMATCH(user->get_fd());
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
