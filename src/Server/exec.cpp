#include "Server.hpp"

void Server::exec_cmd(t_parser_data& data, User* &user)
{
	// TODO refuse action if not connceted exeption: CAP NICK USER PASS

	static std::map<std::string, void (Server::*)(t_parser_data& data, User* &user)> commandMap;
	if (commandMap.empty()) {
		commandMap["CAP"] = &Server::CAP;
		commandMap["NICK"] = &Server::NICK;
		commandMap["USER"] = &Server::USER;
		commandMap["PASS"] = &Server::PASS;
		commandMap["PING"] = &Server::PING;
		commandMap["JOIN"] = &Server::JOIN;
		commandMap["QUIT"] = &Server::QUIT;
		commandMap["MODE"] = &Server::MODE;
		commandMap["KICK"] = &Server::KICK;
		commandMap["TOPIC"] = &Server::TOPIC;
		commandMap["PRIVMSG"] = &Server::PRIVMSG;
		commandMap["INVITE"]= &Server::INVITE;
		commandMap["NOTICE"]= &Server::NOTICE;
	}

	std::map<std::string, void (Server::*)(t_parser_data& data, User* &user)>::iterator it = commandMap.find(data.cmd[0]);

	if (it != commandMap.end()) {
		(this->*(it->second))(data, user);
	} else {
		Numerics::_421_ERR_UNKNOWNCOMMAND("*", data.cmd[0], user->get_fd());
	}
}

void	Server::try_register(User* &user)
{
	
	if (user->get_nickname().empty())
	{
		// TODO https://modern.ircdocs.horse/#errnonicknamegiven-431
		std::clog << "Nick not set\n";
		return;
	}

	if (!user->get_have_valid_password())
	{
		Numerics::_464_ERR_PASSWDMISMATCH(user->get_nickname(), user->get_fd());
		return;
	}
	
	user->set_is_register(true);
	Numerics::_001_RPL_WELCOME(user->get_fd(), user->get_nickname());
}

// https://ircv3.net/specs/extensions/capability-negotiation.html
