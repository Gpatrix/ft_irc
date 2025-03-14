#include "Server.hpp"

void Server::exec_cmd(t_parser_data& data, User* &user)
{
	static std::set<std::string> CommandsNoRegister ;
	if (CommandsNoRegister.empty()) {
		CommandsNoRegister.insert("CAP");
		CommandsNoRegister.insert("NICK");
		CommandsNoRegister.insert("USER");
		CommandsNoRegister.insert("PASS");
		CommandsNoRegister.insert("PING");
	}
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
		commandMap["PART"] = &Server::PART;
		commandMap["TOPIC"] = &Server::TOPIC;
		commandMap["INVITE"]= &Server::INVITE;
		commandMap["NOTICE"]= &Server::NOTICE;
		commandMap["PRIVMSG"] = &Server::PRIVMSG;
	}

 	std::map<std::string, void (Server::*)(t_parser_data& data, User* &user)>::iterator it = commandMap.find(data.cmd[0]);

	if (it != commandMap.end() && (user->get_is_register() || CommandsNoRegister.count(data.cmd[0]) > 0))
		(this->*(it->second))(data, user);
	else 
		Numerics::_421_ERR_UNKNOWNCOMMAND("*", data.cmd[0], user->get_fd());
}

void	Server::try_register(User* &user)
{
	
	if (user->get_nickname().empty())
	{
		Numerics::_431_ERR_NONICKNAMEGIVEN(user->get_nickname(), user->get_fd());
		return;
	}

	if (!user->get_have_valid_password() && !this->Password.empty())
	{
		Numerics::_464_ERR_PASSWDMISMATCH(user->get_nickname(), user->get_fd());
		return;
	}
	
	user->set_is_register(true);
	Numerics::_001_RPL_WELCOME(user->get_nickname(), user->get_fd());
}
